#include "stdafx.h"
#include "GameEngine.h"
#include "../MasterEngineLibShared/Time.h"
#include "Renderer.h"
#include "../MasterEngineLibShared/Input.h"
#include <iostream>
#include "ThreadPool.h"
#include "GameObject.h"
#include <numeric>

namespace MasterEngine {
	namespace LibAggregator {

		using namespace LibShared;

		unsigned long long GameEngine::incremental_id_{};
		std::vector<GameObject*> GameEngine::game_objects_{};
		std::vector<GameObject*> GameEngine::collision_game_objects_{};
		std::unordered_set<GameObject*> GameEngine::destroyed_game_objects_{};
		std::vector<float> GameEngine::delta_list_{};

		std::mutex GameEngine::add_game_object_mutex_{};
		std::mutex GameEngine::remove_game_object_mutex_{};
		std::mutex GameEngine::modify_collision_mutex_{};
		ThreadPool GameEngine::thread_pool_{};

		void GameEngine::init()
		{
#ifdef LOG_DELTA_TIMES
			delta_list_ = std::vector<float>{};
#endif
			thread_pool_.CreateThreadPool();
			Time::StartUp();

		}

		void GameEngine::run()
		{
#ifdef LOG_DELTA_TIMES
			float com_delta = 0;
			int framecount = 0;
#endif

			while (Renderer::is_open())
			{
				//Create delta for this frame
				Time::Update();

#ifdef LOG_DELTA_TIMES
				delta_list_.emplace_back(Time::DeltaTime());
				com_delta += Time::DeltaTime();
				framecount++;
				if (com_delta > 1.0f)
				{
					com_delta -= 1.0f;
					std::cout << "Frame per second: " << framecount << std::endl;
					framecount = 0;
				}
#endif

				sf::Event event;
				while (Renderer::poll_event(event))
				{
					if (event.type == sf::Event::Closed)
					{
						Renderer::close();
					}
				}

				Input::process_input();

				auto& game_state = get_gamestate();
				for (auto i = 0; i < game_state.size(); i++) {
					auto* object = game_state[i];

					thread_pool_.AddJob(std::bind(&GameObject::update, object));
				}

				for (auto i = 0; i < collision_game_objects_.size(); i++) {

					auto* object = collision_game_objects_[i];
					thread_pool_.AddJob(std::bind(&GameObject::collision_check, object));
				}

				Renderer::render();

				{
					//Wait for every thing to be done
					std::unique_lock<std::mutex> lock(thread_pool_.Queue_Mutex);
					thread_pool_.condition_done.wait(lock, [] {return thread_pool_.JobQueue.empty() && thread_pool_.working_threads_ == 0; });
					//std::cout << ThreadPool::working_threads_ << std::endl;
				}

				//TODO Impement the aggregator step
				unsigned reducesteps = thread_pool_.thread_count;
				while (reducesteps != 1)
				{
					unsigned halffloor = reducesteps / 2;
					unsigned halfroff = (reducesteps + 1) / 2;

					for (auto i = 0; i < halffloor; i++) {
						thread_pool_.AddJob(std::bind(&GameEngine::mergelist, ThreadPool::threads_ids[i], ThreadPool::threads_ids[i+ halfroff]));
					}

					{
						std::unique_lock<std::mutex> lock(thread_pool_.Queue_Mutex);
						thread_pool_.condition_done.wait(lock, [] {return thread_pool_.JobQueue.empty() && thread_pool_.working_threads_ == 0; });
						//std::cout << ThreadPool::working_threads_ << std::endl;
					}
					reducesteps = halfroff;
				}
				for (auto delta : thread_pool_.deltas[ThreadPool::threads_ids[0]]) {
					BaseDelta* object = delta.second;
					thread_pool_.AddJob(std::bind(&BaseDelta::merge, object));
				}
				for (auto* go : destroyed_game_objects_)
				{
					delete go;
				}
				get_destroyid_game_object().clear();

				
			}

			thread_pool_.terminate();

#ifdef LOG_DELTA_TIMES
			const auto total_time = std::accumulate(delta_list_.begin(), delta_list_.end(), 0.0f);
			const auto total_frames = delta_list_.size();
			const auto frames_over_time = total_frames / total_time;

			std::cout << "Total time: " << total_time << std::endl;
			std::cout << "Total frames: " << total_frames << std::endl;
			std::cout << "Total Frames/second: " << frames_over_time << std::endl;

#endif


		}

		unsigned long long GameEngine::get_new_id()
		{
			return ++incremental_id_;
		}

		void GameEngine::Instantiate(GameObject* game_object, sf::Vector2f position)
		{
			game_object->set_position(position);
			game_object->start_up();
		}

		void GameEngine::add_game_object(GameObject* game_object)
		{
			std::unique_lock<std::mutex> lock(add_game_object_mutex_);
			game_objects_.emplace_back(game_object);
		}

		void GameEngine::add_collider(GameObject* game_object)
		{
			std::unique_lock<std::mutex> lock(modify_collision_mutex_);
			collision_game_objects_.emplace_back(game_object);
		}

		void GameEngine::remove_collider(GameObject* game_object)
		{
			std::unique_lock<std::mutex> lock(modify_collision_mutex_);
			collision_game_objects_.erase(std::find(collision_game_objects_.begin(), collision_game_objects_.end(), game_object));
		}

		void GameEngine::remove_game_object(GameObject* game_object)
		{
			std::unique_lock<std::mutex> lock(remove_game_object_mutex_);
			destroyed_game_objects_.insert(game_object);
		}

		std::vector<GameObject*>& GameEngine::get_gamestate()
		{
			return game_objects_;
		}

		std::unordered_set<GameObject*>& GameEngine::get_destroyid_game_object()
		{
			return destroyed_game_objects_;
		}
		void GameEngine::mergelist(std::thread::id deltas1, std::thread::id deltas2)
		{
			auto* delta_list1 = &MasterEngine::LibAggregator::ThreadPool::deltas[deltas1];

			for (auto deltas : ThreadPool::deltas[deltas2])
			{
				if (delta_list1->find(deltas.first) != delta_list1->end())
				{
					delta_list1->at(deltas.first)->reduce(deltas.second);
					//TODO should delete element in deltas2
				}
				else
				{
					delta_list1->insert(std::pair<void*, BaseDelta*>(deltas.first, deltas.second));
				}
			}
		}
	}
}
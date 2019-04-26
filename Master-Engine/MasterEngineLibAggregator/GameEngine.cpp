#include "stdafx.h"
#include "GameEngine.h"
#include "../MasterEngineLibShared/Time.h"
#include "Renderer.h"
#include "../MasterEngineLibShared/Input.h"
#include <iostream>
#include "ThreadPool.h"
#include "GameObject.h"
#include <numeric>
#include "../CaptainEverythingAggregator/Spawner.h"
#include "../CaptainEverythingShared/Constants.h"

namespace MasterEngine {
	namespace LibAggregator {

		using namespace LibShared;

		unsigned long long GameEngine::incremental_id_{};
		VectorWrapper<GameObject*> GameEngine::game_objects_{};
		VectorWrapper<GameObject*> GameEngine::collision_game_objects_{};
		std::unordered_set<GameObject*> GameEngine::destroyed_game_objects{};

#ifdef LOG_DELTA_TIMES
		std::vector<float> GameEngine::delta_list_{};
#endif
#ifdef LOG_CUMULATIVE_TIME
		long long GameEngine::frame_count_{};
		float GameEngine::cumulative_time_{};
#endif

		ThreadPool GameEngine::thread_pool_{};

		void GameEngine::init()
		{
#ifdef LOG_DELTA_TIMES
			delta_list_ = std::vector<float>{};
#endif
			thread_pool_.create_thread_pool();
			Time::start_up();


			auto* spawner = new CaptainEverythingAggregator::Spawner();
			instantiate(spawner);
			std::vector<GameObject*> container = {};
			container.emplace_back(spawner);
			game_objects_.adds_vector(container);
		}

		void GameEngine::run()
		{
#ifdef LOG_DELTA_TIMES
			float com_delta = 0;
			int framecount = 0;
#endif
#ifdef LOG_CUMULATIVE_TIME
			frame_count_ = 0;
			cumulative_time_ = 0;
#endif

			while (Renderer::is_open())
			{
				//Create delta for this frame
				Time::tick();

#ifdef LOG_DELTA_TIMES
				delta_list_.emplace_back(Time::delta_time());
				com_delta += Time::delta_time();
				framecount++;
				if (com_delta > 1.0f)
				{
					com_delta -= 1.0f;
					std::cout << "Frame per second: " << framecount << std::endl;
					framecount = 0;
				}
#endif
#ifdef LOG_CUMULATIVE_TIME
				cumulative_time_ += Time::delta_time();
				if (cumulative_time_ > CaptainEverythingShared::Constants::record_time_start)
				{
					++frame_count_;
				}
#endif

				sf::Event event{};
				while (Renderer::poll_event(event))
				{
					if (event.type == sf::Event::Closed)
					{
						Renderer::close();
					}
				}
				if (cumulative_time_ > CaptainEverythingShared::Constants::record_time_end)
				{
					Renderer::close();
				}

				

				auto& game_state = get_game_state();
				for (auto i = 0; i < game_state.size(); i++) {
					auto* object = game_state[i];
					if (!object->need_input())
					{
						thread_pool_.add_job(std::bind(&GameObject::update, object));
					}
				}

				for (auto i = 0; i < collision_game_objects_.get_value().size(); i++) {
					auto object = collision_game_objects_.get_value()[i];
					if (!object->need_input())
					{
						thread_pool_.add_job(std::bind(&GameObject::collision_check, object));
					}
				}
				Input::process_input();

				for (auto i = 0; i < game_state.size(); i++) {
					auto* object = game_state[i];
					if (object->need_input())
					{
						thread_pool_.add_job(std::bind(&GameObject::update, object));
					}
				}

				for (auto i = 0; i < collision_game_objects_.get_value().size(); i++) {
					auto object = collision_game_objects_.get_value()[i];
					if (object->need_input())
					{
						thread_pool_.add_job(std::bind(&GameObject::collision_check, object));
					}
				}

				Renderer::render();

				{
					//Wait for every thing to be done
					std::unique_lock<std::mutex> lock(thread_pool_.queue_mutex);
					thread_pool_.condition_done.wait(lock, [] {return thread_pool_.job_queue.empty() && thread_pool_.working_threads == 0; });
				}

				///Aggregator step start
				auto reduction_steps = thread_pool_.thread_count;
				while (reduction_steps != 1)
				{
					const auto floor = reduction_steps / 2;
					const auto ceil = (reduction_steps + 1) / 2;

					for (unsigned i = 0; i < floor; i++) {
						const int index = i + ceil;
						thread_pool_.add_job(std::bind(&GameEngine::merge_list, ThreadPool::threads_ids[i], ThreadPool::threads_ids[index]));
					}

					{
						std::unique_lock<std::mutex> lock(thread_pool_.queue_mutex);
						thread_pool_.condition_done.wait(lock, [] {return thread_pool_.job_queue.empty() && thread_pool_.working_threads == 0; });
					}
					reduction_steps = ceil;
				}
				for (const auto delta : ThreadPool::deltas[ThreadPool::threads_ids[0]]) {
					auto object = delta.second;
					thread_pool_.add_job(std::bind(&BaseDelta::merge, object));
				}
				{
					std::unique_lock<std::mutex> lock(thread_pool_.queue_mutex);
					thread_pool_.condition_done.wait(lock, [] {return thread_pool_.job_queue.empty() && thread_pool_.working_threads == 0; });
				}

				for (auto delta: ThreadPool::deltas[ThreadPool::threads_ids[0]])
				{
					delete delta.second;
				}
				for (auto id : ThreadPool::threads_ids)
				{
					ThreadPool::deltas[id].clear();
				}
				///Aggregator step End

				for (auto* game_object: destroyed_game_objects)
				{
					delete game_object;
				}
				destroyed_game_objects.clear();

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
#ifdef LOG_CUMULATIVE_TIME
			/*std::cout << "Total time: " << cumulative_time_ << std::endl;
			std::cout << "Recording time: " << (cumulative_time_ - CaptainEverythingShared::Constants::record_time_start) << std::endl;
			std::cout << "Total frames: " << frame_count_ << std::endl;
			std::cout << "Total frames/second: " << frame_count_ / (cumulative_time_ - CaptainEverythingShared::Constants::record_time_start) << std::endl;
*/
			std::cout << cumulative_time_ << ";" << (cumulative_time_ - CaptainEverythingShared::Constants::record_time_start) << ";" << frame_count_ << ";" << frame_count_ / (cumulative_time_ - CaptainEverythingShared::Constants::record_time_start) << ";" << std::endl;
#endif

		}

		unsigned long long GameEngine::get_new_id()
		{
			return ++incremental_id_;
		}

		void GameEngine::instantiate(GameObject* game_object)
		{
			thread_pool_.add_job(std::bind(&GameObject::start_up, game_object));
		}

		void GameEngine::add_game_object(GameObject* game_object)
		{
			game_objects_ += game_object;
		}

		void GameEngine::add_collider(GameObject* game_object)
		{
			collision_game_objects_ += (game_object);
		}

		void GameEngine::remove_collider(GameObject* game_object)
		{
			collision_game_objects_ -= game_object;
		}

		void GameEngine::remove_game_object(GameObject* game_object)
		{
			game_objects_ -= game_object;
			game_object->remove_game_object();
		}

		std::vector<GameObject*>& GameEngine::get_game_state()
		{
			return game_objects_.get_value();
		}

		std::unordered_set<GameObject*>& GameEngine::get_destroyed_game_object()
		{
			return destroyed_game_objects;
		}

		void GameEngine::merge_list(const std::thread::id delta_1, const std::thread::id delta_2)
		{
			auto* delta_list1 = &ThreadPool::deltas[delta_1];

			for (auto deltas : ThreadPool::deltas[delta_2])
			{
				if (delta_list1->find(deltas.first) != delta_list1->end())
				{
					delta_list1->at(deltas.first)->reduce(deltas.second);
					delete deltas.second;
				}
				else
				{
					delta_list1->insert(std::pair<void*, BaseDelta*>(deltas.first, deltas.second));
				}
			}
		}
	}
}

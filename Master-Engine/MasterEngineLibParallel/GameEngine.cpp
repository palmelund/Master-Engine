#include "stdafx.h"
#include "GameEngine.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibParallel/Renderer.h"
#include "../MasterEngineLibShared/Input.h"
#include <iostream>
#include "ThreadPool.h"
#include "GameObject.h"
#include <numeric>
#include <fstream>
#include "../CaptainEverythingShared/Constants.h"

namespace MasterEngine {
	namespace LibParallel {

		using namespace LibShared;

		unsigned long long GameEngine::incremental_id_{};
		std::vector<GameObject*> GameEngine::game_objects_{};
		std::vector<GameObject*> GameEngine::collision_game_objects_{};
		std::unordered_set<GameObject*> GameEngine::destroyed_game_objects_{};

#ifdef LOG_DELTA_TIMES
		std::vector<float> GameEngine::delta_list_{};
#endif

#ifdef LOG_CUMULATIVE_TIME
		long long GameEngine::frame_count_{};
		float GameEngine::cumulative_time_{};
#endif

		std::mutex GameEngine::add_game_object_mutex_{};
		std::mutex GameEngine::remove_game_object_mutex_{};
		std::mutex GameEngine::modify_collision_mutex_{};
		ThreadPool GameEngine::thread_pool_{};

		void GameEngine::init()
		{
#ifdef LOG_DELTA_TIMES
			delta_list_ = std::vector<float>{};
#endif
			thread_pool_.create_thread_pool();
			Time::start_up();

		}

		void GameEngine::run()
		{
#ifdef LOG_DELTA_TIMES
			auto com_delta = 0.0f;
			auto frame_count = 0;
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
				frame_count++;
				if (com_delta > 1.0f)
				{
					com_delta -= 1.0f;
					std::cout << "Frame per second: " << frame_count << std::endl;
					frame_count = 0;
				}
#endif

#ifdef LOG_CUMULATIVE_TIME
				cumulative_time_ += Time::delta_time();
				if (cumulative_time_ > CaptainEverythingShared::Constants::record_time_start)
				{
					++frame_count_;
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

				if (cumulative_time_ > CaptainEverythingShared::Constants::record_time_end)
				{
					Renderer::close();
				}

				Input::process_input();

				//for (GameObject* object : get_game_state()) {
				auto& game_state = get_game_state();
				for (auto i = 0; i < game_state.size(); i++) {
					auto* object = game_state[i];

					thread_pool_.add_job(std::bind(&GameObject::update, object));
				}
				{
					std::unique_lock<std::mutex> lock(thread_pool_.queue_mutex);
					thread_pool_.condition_done.wait(lock, [] {return thread_pool_.job_queue.empty() && thread_pool_.working_threads_ == 0; });
				}

				//for (GameObject* object : collision_game_objects_) {
				for (auto i = 0; i < collision_game_objects_.size(); i++) {
				//object->collision_check();
					auto* object = collision_game_objects_[i];
					thread_pool_.add_job(std::bind(&GameObject::collision_check, object));
				}

				{
					std::unique_lock<std::mutex> lock(thread_pool_.queue_mutex);
					thread_pool_.condition_done.wait(lock, [] {return thread_pool_.job_queue.empty() && thread_pool_.working_threads_ == 0; });
					//std::cout << ThreadPool::working_threads_ << std::endl;
				}

				/*for (int i = 0; i < destroyed_game_objects_.size(); i++)
				{
					delete destroyed_game_objects_[i];
				}*/

				for (auto* go : destroyed_game_objects_)
				{
					delete go;
				}
				get_destroyed_game_objects().clear();

				Renderer::render();
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
			std::ofstream myfile;
			myfile.open("test_results.txt", std::ios::out | std::ios::app);


			myfile << cumulative_time_ << ";" << (cumulative_time_ - CaptainEverythingShared::Constants::record_time_start) << ";" << frame_count_ << ";" << frame_count_ / (cumulative_time_ - CaptainEverythingShared::Constants::record_time_start) << ";" << std::endl;

			myfile.close(); 
#endif

		}

		unsigned long long GameEngine::get_new_id()
		{
			return ++incremental_id_;
		}

		void GameEngine::instantiate(GameObject* game_object, const sf::Vector2f position)
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

		std::vector<GameObject*>& GameEngine::get_game_state()
		{
			return game_objects_;
		}

		std::unordered_set<GameObject*>& GameEngine::get_destroyed_game_objects()
		{
			return destroyed_game_objects_;
		}
	}
}

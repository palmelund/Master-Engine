#include "stdafx.h"
#include "GameEngine.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibSequential/Renderer.h"
#include "../MasterEngineLibShared/Input.h"
#include <iostream>
#include "../CaptainEverythingShared/Constants.h"
#include <fstream>
namespace MasterEngine {
	namespace LibSequential {

		using namespace LibShared;

		unsigned long long GameEngine::incremental_id_{};
		std::unordered_set<GameObject*> GameEngine::game_objects_{};
		std::unordered_set<GameObject*> GameEngine::collision_game_object_{};
		std::unordered_set<GameObject*> GameEngine::destroyed_game_object_{};

#ifdef LOG_DELTA_TIMES
		std::vector<float> GameEngine::delta_list_{};
#endif

#ifdef LOG_CUMULATIVE_TIME
		long long GameEngine::frame_count_{};
		float GameEngine::cumulative_time_{};
#endif

		void GameEngine::init()
		{
#ifdef LOG_DELTA_TIMES
			delta_list_ = std::vector<float>{};
#endif

			Time::start_up();

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

				Input::process_input();

				for (auto object : get_game_state()) {
					object->update();
				}
				for (auto object : collision_game_object_) {
					object->collision_check();
				}

				for (auto game_object : get_destroyed_game_objects())
				{
					delete game_object;
				}
				get_destroyed_game_objects().clear();

				Renderer::render();
			}

#ifdef LOG_DELTA_TIMES
			const auto total_time = std::accumulate(delta_list_.begin(), delta_list_.end(), 0.0f);
			const auto total_frames = delta_list_.size();
			const auto frames_over_time = total_frames / total_time;

			std::cout << "Total time: " << total_time << std::endl;
			std::cout << "Total frames: " << total_frames << std::endl;
			std::cout << "Total Frames/second: " << frames_over_time << std::endl;

#endif

#ifdef LOG_CUMULATIVE_TIME
			//std::cout << "Total time: " << cumulative_time_ << std::endl;
			//std::cout << "Recording time: " << (cumulative_time_ - CaptainEverythingShared::Constants::record_time_start) << std::endl;
			//std::cout << "Total frames: " << frame_count_ << std::endl;
			//std::cout << "Total frames/second: " << frame_count_ / (cumulative_time_- CaptainEverythingShared::Constants::record_time_start) << std::endl;

			std::ofstream myfile;
			myfile.open("test_results.txt", std::ios::out | std::ios::app);


			myfile << cumulative_time_ << ";" << (cumulative_time_ - CaptainEverythingShared::Constants::record_time_start) << ";" << frame_count_ << ";" << frame_count_ / (cumulative_time_ - CaptainEverythingShared::Constants::record_time_start) << ";" << std::endl;

			myfile.close();
#endif#endif
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
			game_objects_.insert(game_object);
		}

		void GameEngine::add_collider(GameObject* game_object)
		{
			collision_game_object_.insert(game_object);
		}

		void GameEngine::remove_collider(GameObject* game_object)
		{
			collision_game_object_.erase(game_object);
		}

		void GameEngine::remove_game_object(GameObject* game_object)
		{
			destroyed_game_object_.insert(game_object);
		}

		std::unordered_set<GameObject*>& GameEngine::get_game_state()
		{
			return game_objects_;
		}

		std::unordered_set<GameObject*>& GameEngine::get_destroyed_game_objects()
		{
			return destroyed_game_object_;
		}
	}
}

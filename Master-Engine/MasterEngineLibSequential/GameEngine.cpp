#include "stdafx.h"
#include "GameEngine.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibSequential/Renderer.h"
#include "../MasterEngineLibShared/Input.h"
#include <iostream>
#include <numeric>

namespace MasterEngine {
	namespace LibSequential {

		using namespace LibShared;

		unsigned long long GameEngine::incremental_id_{};
		std::unordered_set<GameObject*> GameEngine::game_objects_{};
		std::unordered_set<GameObject*> GameEngine::collision_game_object_{};
		std::unordered_set<GameObject*> GameEngine::destroyid_game_object_{};
		std::vector<float> GameEngine::delta_list_{};

		void GameEngine::init()
		{
#ifdef LOG_DELTA_TIMES
			delta_list_ = std::vector<float>{};
#endif

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

				for (GameObject* object : get_gamestate()) {
					object->update();
				}
				for (GameObject* object : collision_game_object_) {
					object->collision_check();
				}

				for (GameObject* game_object : get_destroyid_game_object())
				{
					delete game_object;
				}
				get_destroyid_game_object().clear();

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
			destroyid_game_object_.insert(game_object);
		}

		std::unordered_set<GameObject*>& GameEngine::get_gamestate()
		{
			return game_objects_;
		}

		std::unordered_set<GameObject*>& GameEngine::get_destroyid_game_object()
		{
			return destroyid_game_object_;
		}
	}
}

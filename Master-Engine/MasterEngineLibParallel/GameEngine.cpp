#include "stdafx.h"
#include "GameEngine.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibParallel/Renderer.h"
#include "../MasterEngineLibShared/Input.h"
#include <iostream>
#include "../MasterEngineLibShared/ThreadPool.h"
#include "GameObject.h"

namespace MasterEngine {
	namespace LibParallel {

		using namespace LibShared;

		unsigned long long GameEngine::incremental_id_{};
		std::vector<GameObject*> GameEngine::game_objects_{};
		std::unordered_set<GameObject*> GameEngine::collision_game_objects_{};
		std::unordered_set<GameObject*> GameEngine::destroyed_game_objects_{};
		std::vector<float> GameEngine::delta_list_{};

		std::mutex GameEngine::add_game_object_mutex_{};
		std::mutex GameEngine::remove_game_object_mutex_{};
		std::mutex GameEngine::modify_collision_mutex_{};

		void GameEngine::init()
		{
#ifdef LOG_DELTA_TIMES
			delta_list_ = std::vector<float>{};
#endif
			ThreadPool::CreateThreadPool();
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
					ThreadPool::AddJob(std::bind(&GameObject::update, object));
				}
				{
					std::unique_lock<std::mutex> lock(ThreadPool::Queue_Mutex);
					ThreadPool::condition_done.wait(lock, [] {return ThreadPool::JobQueue.empty(); });
				}

				for (GameObject* object : collision_game_objects_) {
					//object->collision_check();
					ThreadPool::AddJob(std::bind(&GameObject::collision_check, object));
				}

				{
					std::unique_lock<std::mutex> lock(ThreadPool::Queue_Mutex);
					ThreadPool::condition_done.wait(lock, [] {return ThreadPool::JobQueue.empty(); });
				}

				for (GameObject* game_object : get_destroyid_game_object())
				{
					delete game_object;
				}
				get_destroyid_game_object().clear();

				Renderer::render();
			}

			ThreadPool::terminate();
			
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
			collision_game_objects_.insert(game_object);
		}

		void GameEngine::remove_collider(GameObject* game_object)
		{
			std::unique_lock<std::mutex> lock(modify_collision_mutex_);
			collision_game_objects_.erase(game_object);
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
	}
}
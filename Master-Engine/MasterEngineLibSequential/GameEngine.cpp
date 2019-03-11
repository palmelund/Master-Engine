#include "stdafx.h"
#include "GameEngine.h"
#include "../MasterEngineLibSequential/partical.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibSequential/Renderer.h"
#include "../MasterEngineLibShared/Input.h"
#include <iostream>

unsigned long long GameEngine::incremental_id_{};
std::unordered_set<GameObject*> GameEngine::game_objects_{};
std::queue<GameObject*> GameEngine::destroyid_game_object_{};
std::vector<float> GameEngine::delta_list_{};

void GameEngine::init()
{
#ifdef LOG_DELTA_TIMES
	delta_list_ = std::vector<float>{};
#endif

	Time::StartUp();
	
	for (GameObject* object : get_gamestate()) {
		object->start_up();
	}
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
		if(com_delta > 1.0f)
		{
			com_delta -= 1.0f;
			std::cout << "Frame per second: " << framecount << std::endl;
			framecount = 0;
		}
#endif
		
		sf::Event event;
		while(Renderer::poll_event(event))
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

		for (GameObject* object : get_gamestate()) {
			object->collision_check();
		}

		while (!get_destroyid_game_object().empty())
		{
			GameObject* remove = get_destroyid_game_object().front();
			get_destroyid_game_object().pop();
			delete remove;
		}
		Renderer::render();
	}
}

unsigned long long GameEngine::get_new_id()
{
	return ++incremental_id_;
}

void GameEngine::add_game_object(GameObject* game_object)
{
	game_objects_.insert(game_object);
}

void GameEngine::remove_game_object(GameObject* game_object)
{
	destroyid_game_object_.push(game_object);
}

std::unordered_set<GameObject*>& GameEngine::get_gamestate()
{
	return game_objects_;
}

std::queue<GameObject*>& GameEngine::get_destroyid_game_object()
{
	return destroyid_game_object_;
}
#include "pch.h"
#include "GameEngine.h"
#include "ResourceManager.h"
#include "Time.h"
#include "Renderer.h"
#include "Input.h"
#include "GameObject.h"
#include "GameState.h"
#include "Player.h"
#include "Wall.h"

GameEngine::GameEngine()
{
	delta_list = std::vector<float>{};
}

GameEngine::~GameEngine()
{

}

void GameEngine::init()
{
	Time::StartUp();
	new Player{"awesomeface.png"};
	
	for(int i = 0; i < 10; i++)
	{
		new Wall{ "wall.png" , sf::Vector2f{200.0f, 0.0f + (20.0f * i)}, 20.0f };
	}

	for (int i = 0; i < 11; i++)
	{
		new Wall{ "wall.png" , sf::Vector2f{200.0f-(20*i), 220.0f}, 20.0f };
	}
	
	for (GameObject* object : GameState::get_gamestate()) {
		object->start_up();
	}
}

void GameEngine::run()
{
	float com_delta = 0;
	int framecount = 0;

	while (Renderer::is_open())
	{
		//Create delta for this frame
		Time::Update();

		delta_list.emplace_back(Time::DeltaTime());
		com_delta += Time::DeltaTime();
		framecount++;
		if(com_delta > 1.0f)
		{
			com_delta -= 1.0f;
			std::cout << "Frame per second: " << framecount << std::endl;
			framecount = 0;
		}

		
		sf::Event event;
		while(Renderer::poll_event(event))
		{
			if (event.type == sf::Event::Closed)
			{
				Renderer::close();
			}
		}

		Input::process_input();
		
		for (GameObject* object : GameState::get_gamestate()) {
			object->update();
		}

		for (GameObject* object : GameState::get_gamestate()) {
			object->collision_check();
		}

		Renderer::render();
	}
}
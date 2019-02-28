#include "pch.h"
#include "GameEngine.h"
#include "ResourceManager.h"
#include "Time.h"
#include "Renderer.h"
#include "Input.h"

GameEngine::GameEngine()
{
	
}

GameEngine::~GameEngine()
{

}

void GameEngine::init()
{
	Time::StartUp();
}

void GameEngine::run()
{
	while (Renderer::is_open())
	{
		//Create delta for this frame
		Time::Update();
		
		sf::Event event;
		while(Renderer::poll_event(event))
		{
			if (event.type == sf::Event::Closed)
			{
				Renderer::close();
			}
		}

		Input::process_input();
		
		//if (get_key(KeyCode::key_a) == KeyStatus::hold)
		//{
		//	p_x -= speed * delta_time_;
		//}

		//if (get_key(KeyCode::key_d) == KeyStatus::hold)
		//{
		//	p_x += speed * delta_time_;
		//}

		//if(get_key(KeyCode::key_w) == KeyStatus::hold)
		//{
		//	p_y -= speed * delta_time_;
		//}

		//if (get_key(KeyCode::key_s) == KeyStatus::hold)
		//{
		//	p_y += speed * delta_time_;
		//}

		Renderer::render();
	}
}
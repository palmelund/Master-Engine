#include "pch.h"
#include "GameEngine.h"
#include "ResourceManager.h"
#include "Time.h"
#include "Renderer.h"

GameEngine::GameEngine()
{
	
}

GameEngine::~GameEngine()
{

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

		process_input();
		
		//if (get_key(key_code::key_a) == key_status::hold)
		//{
		//	p_x -= speed * delta_time_;
		//}

		//if (get_key(key_code::key_d) == key_status::hold)
		//{
		//	p_x += speed * delta_time_;
		//}

		//if(get_key(key_code::key_w) == key_status::hold)
		//{
		//	p_y -= speed * delta_time_;
		//}

		//if (get_key(key_code::key_s) == key_status::hold)
		//{
		//	p_y += speed * delta_time_;
		//}

		Renderer::render();
	}
}

key_status GameEngine::get_key(key_code key)
{
	return key_statuses_[static_cast<long long int>(key)];
}

void GameEngine::process_input()
{
	process_key_input(sf::Keyboard::W, key_code::key_w);
	process_key_input(sf::Keyboard::A, key_code::key_a);
	process_key_input(sf::Keyboard::S, key_code::key_s);
	process_key_input(sf::Keyboard::D, key_code::key_d);
}

void GameEngine::process_key_input(sf::Keyboard::Key gl_key, key_code key)
{
	if (sf::Keyboard::isKeyPressed(gl_key))
	{
		if (key_statuses_[static_cast<unsigned long long>(key)] == key_status::unpressed || key_statuses_[static_cast<unsigned long long>(key)] == key_status::lifted)
		{
			key_statuses_[static_cast<unsigned long long>(key)] = key_status::pressed;
		}
		else
		{
			key_statuses_[static_cast<unsigned long long>(key)] = key_status::hold;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(gl_key) && (key_statuses_[static_cast<unsigned long long>(key)] == key_status::pressed || key_statuses_[static_cast<unsigned long long>(key)] == key_status::hold))
	{
		key_statuses_[static_cast<unsigned long long>(key)] = key_status::lifted;
	}
	else
	{
		key_statuses_[static_cast<unsigned long long>(key)] = key_status::unpressed;
	}
}
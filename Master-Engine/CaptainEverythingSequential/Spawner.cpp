#include "pch.h"
#include "Spawner.h"
#include "../MasterEngineLibShared/Time.h"
#include "Enemy.h"
#include "../MasterEngineLibSequential/ResourceManager.h"
#include "../MasterEngineLibSequential/Renderer.h"
#include "../MasterEngineLibSequential/GameEngine.h"
#include "Player.h"
#include "BackgroundElement.h"
#include "Boss.h"


Spawner::Spawner() : GameObject(false)
{
	internal_timer = 0;
	spawn_time = 0.8f;
	spawn_position_ = 0.0f;
}


Spawner::~Spawner()
{
	
}

void Spawner::start_up()
{
	GameEngine::Instantiate(new Player(), sf::Vector2f{50.0f, Renderer::get_window_size()->y/2.0f });
	GameEngine::Instantiate(new Boss(), sf::Vector2f{ Renderer::get_window_size()->x+100.0f, Renderer::get_window_size()->y / 2.0f });


	for(int i = 0 ; i < 150; i++)
	{
		GameEngine::Instantiate(new BackgroundElement(), sf::Vector2f{ (float)((70*i)%Renderer::get_window_size()->x),(float)( (30 * i) % Renderer::get_window_size()->y )});
	}

}

void Spawner::update()
{
	internal_timer += Time::DeltaTime();
	if (internal_timer > spawn_time)
	{
		internal_timer -= spawn_time;
		spawn_position_ += 300.0f;
		spawn_position_ = int(spawn_position_) % (Renderer::get_window_size()->y-30);
		GameEngine::Instantiate(new Enemy("enemy.png"), sf::Vector2f{ Renderer::get_window_size()->x + 100.0f, spawn_position_ });
		
	}
}

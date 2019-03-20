#include "pch.h"
#include "Spawner.h"
#include "../MasterEngineLibShared/Time.h"
#include "Enemy.h"
#include "../MasterEngineLibParallel/Renderer.h"
#include "../MasterEngineLibParallel/GameEngine.h"
#include "Player.h"
#include "BackgroundElement.h"
#include "Boss.h"
#include "GravityWell.h"

namespace CaptainEverythingParallel {

	Spawner* Spawner::single_ton_ = nullptr;

	Spawner::Spawner() : GameObject(false)
	{
		internal_timer = 0;
		spawn_time = 0.8f;
		spawn_position_ = 0.0f;
		player_hits_ = 0;
		enemy_kills_ = 0;
		spawn_count_ = 0;
		Spawner::single_ton_ = this;
	}


	Spawner::~Spawner() = default;

	void Spawner::start_up()
	{
		for (int i = 0; i < 1000; i++)
		{
			;
			GameEngine::Instantiate(new BackgroundElement(), sf::Vector2f{ static_cast<float>((70 * i) % Renderer::get_window_size()->x),(float)((30 * i) % Renderer::get_window_size()->y) });
		}

		GameEngine::Instantiate(new Player(), sf::Vector2f{ 50.0f, Renderer::get_window_size()->y / 2.0f });
		GameEngine::Instantiate(new GravityWell(), sf::Vector2f{ Renderer::get_window_size()->x / 2.0f, Renderer::get_window_size()->y / 2.0f });
	}

	void Spawner::update()
	{
		internal_timer += Time::DeltaTime();
		if (internal_timer > spawn_time)
		{
			internal_timer -= spawn_time;
			spawn_position_ += 300.0f;
			spawn_position_ = int(spawn_position_) % (Renderer::get_window_size()->y - 30);
			GameEngine::Instantiate(new Enemy(), sf::Vector2f{ Renderer::get_window_size()->x + 100.0f, spawn_position_ });
			spawn_count_++;
			if (spawn_count_ > 50)
			{
				spawn_count_ = 0;
				GameEngine::Instantiate(new Boss(), sf::Vector2f{ Renderer::get_window_size()->x + 100.0f, Renderer::get_window_size()->y / 2.0f });
			}
		}
		Renderer::draw_text("Kills: " + std::to_string(enemy_kills_), 10, 10, 20);
		Renderer::draw_text("Damage: " + std::to_string(player_hits_), 10, 30, 20);
	}

	void Spawner::add_player_hit()
	{
		std::unique_lock<std::mutex> lock(player_hit_mutex_);
		player_hits_++;
	}

	void Spawner::add_enemy_hit()
	{
		std::unique_lock<std::mutex> lock(enemy_hit_mutex_);
		enemy_kills_++;
	}

	Spawner* Spawner::get_single_ton()
	{
		return Spawner::single_ton_;
	}
}
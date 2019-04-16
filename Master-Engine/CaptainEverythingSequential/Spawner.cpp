#include "pch.h"
#include "Spawner.h"
#include "../MasterEngineLibShared/Time.h"
#include "Enemy.h"
#include "../MasterEngineLibSequential/Renderer.h"
#include "../MasterEngineLibSequential/GameEngine.h"
#include "Player.h"
#include "BackgroundElement.h"
#include "Boss.h"
#include "GravityWell.h"
#include "../CaptainEverythingShared/Constants.h"

namespace CaptainEverythingSequential {
	using namespace MasterEngine::LibShared;

	Spawner* Spawner::single_ton_ = nullptr;

	Spawner::Spawner() : GameObject(false)
	{
		internal_timer = 0;
		spawn_time = ENEMY_SPAWN_TIME;
		spawn_position_ = 0.0f;
		player_hits_ = 0;
		enemy_kills_ = 0;
		spawn_count_ = 0;
		Spawner::single_ton_ = this;
	}


	Spawner::~Spawner()
	{

	}

	void Spawner::start_up()
	{
		for (int i = 0; i < BACKGROUND_ELEMENT_COUNT; i++)
		{
			;
			GameEngine::instantiate(new BackgroundElement(), sf::Vector2f{ static_cast<float>((BACKGROUND_ELEMENT_SIZE * i) % Renderer::get_window_size()->x),(float)((BACKGROUND_ELEMENT_SIZE * i) / Renderer::get_window_size()->x) });
		}

		GameEngine::instantiate(new Player(), sf::Vector2f{ 50.0f, Renderer::get_window_size()->y / 2.0f });
		GameEngine::instantiate(new GravityWell(), sf::Vector2f{ Renderer::get_window_size()->x / 2.0f, Renderer::get_window_size()->y / 2.0f });
	}

	void Spawner::update()
	{
		internal_timer += Time::delta_time();
		if (internal_timer > spawn_time)
		{
			internal_timer -= spawn_time;
			spawn_position_ += 300.0f;
			spawn_position_ = static_cast<float>(int(spawn_position_) % (Renderer::get_window_size()->y - 30));
			GameEngine::instantiate(new Enemy(), sf::Vector2f{ Renderer::get_window_size()->x + 100.0f, spawn_position_ });
			spawn_count_++;
			if (spawn_count_ > BOSS_SPAWN_THRESHOLD)
			{
				spawn_count_ = 0;
				GameEngine::instantiate(new Boss(), sf::Vector2f{ Renderer::get_window_size()->x + 100.0f, Renderer::get_window_size()->y / 2.0f });
			}
		}
		Renderer::draw_text("Kills: " + std::to_string(enemy_kills_), 10, 10, 20);
		Renderer::draw_text("Damage: " + std::to_string(player_hits_), 10, 30, 20);
	}

	void Spawner::add_player_hit()
	{
		player_hits_++;
	}

	void Spawner::add_enemy_hit()
	{
		enemy_kills_++;
	}

	Spawner* Spawner::get_single_ton()
	{
		return Spawner::single_ton_;
	}
}

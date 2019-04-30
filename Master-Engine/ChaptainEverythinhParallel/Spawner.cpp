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
#include "../CaptainEverythingShared/Constants.h"

namespace CaptainEverythingParallel {
	using namespace CaptainEverythingShared;

	Spawner* Spawner::single_ton_ = nullptr;

	Spawner::Spawner() : GameObject(false)
	{
		internal_timer = 0;
		spawn_time = Constants::enemy_spawn_time;;
		spawn_position_ = 0.0f;
		player_hits_ = 0;
		enemy_kills_ = 0;
		spawn_count_ = 0;
		Spawner::single_ton_ = this;
	}


	Spawner::~Spawner() = default;

	void Spawner::start_up()
	{
		for (int i = 0; i < Constants::gravity_wells(); i++)
		{
			GameEngine::instantiate(new GravityWell(), sf::Vector2f{0, 0});
		}

		for (int i = 0; i < Constants::background_elements(); i++)
		{
			GameEngine::instantiate(new BackgroundElement(), sf::Vector2f{ static_cast<float>((Constants::background_element_size * i) % Renderer::get_window_size()->x),(float)((Constants::background_element_size * i) / Renderer::get_window_size()->x) });
		}

		
	}

	void Spawner::update()
	{

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

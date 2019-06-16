#include "pch.h"
#include "Spawner.h"
#include "../MasterEngineLibShared/Time.h"
#include "Enemy.h"
#include "../MasterEngineLibAggregator/Renderer.h"
#include "../MasterEngineLibAggregator/GameEngine.h"
#include "Player.h"
#include "BackgroundElement.h"
#include "Boss.h"
#include "GravityWell.h"
#include "../CaptainEverythingShared/Constants.h"
#include "../CaptainEverythingShared/GenericHelper.h"

namespace CaptainEverythingAggregator {
	using namespace CaptainEverythingShared;

	Spawner* Spawner::single_ton_ = nullptr;

	Spawner::Spawner() : GameObject(false)
	{
		internal_timer = 0;
		spawn_time = Constants::enemy_spawn_time;
		spawn_position_ = 0.0f;
		player_hits_ = 0;
		enemy_kills_ = 0;
		spawn_count_ = 0;
		Spawner::single_ton_ = this;
		enemy_kills_ = {};
		player_hits_ = {};
	}


	Spawner::~Spawner() = default;

	void Spawner::start_up()
	{
		for (int i = 0; i < Constants::gravity_wells(); i++)
		{
			GameEngine::instantiate(new GravityWell(sf::Vector2f{ 0, 0 }));
		}

		for (int i = 0; i < Constants::background_elements(); i++)
		{
			auto pos = GenericHelper::get_position(i);
			pos.x *= Renderer::get_window_size()->x;
			pos.y *= Renderer::get_window_size()->y;

			auto vel = GenericHelper::get_velocity();

			auto* bge = new BackgroundElement(pos);
			bge->set_velocity(vel);

			GameEngine::instantiate(bge);
		}

	}

	void Spawner::update()
	{
	}

	void Spawner::add_player_hit()
	{
		player_hits_ += 1;
	}

	void Spawner::add_enemy_hit()
	{
		enemy_kills_+=1;
	}

	Spawner* Spawner::get_single_ton()
	{
		return Spawner::single_ton_;
	}
}

#include "pch.h"
#include "Enemy.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"
#include "../MasterEngineLibParallel/GameEngine.h"
#include "EnemyBullet.h"
#include <mutex>
#include "../CaptainEverythingShared/SpriteIndexes.h"
#include "../CaptainEverythingShared/Constants.h"

namespace CaptainEverythingParallel {
	using namespace CaptainEverythingShared;

	Enemy::Enemy() : GameObject(false)
	{
		size_ = Constants::enemy_size;
		fire_rate_ = Constants::enemy_fire_rate;
		internal_timer = 0;
		GameObject::set_velocity(sf::Vector2f{ -100.0f, 0.0f });
		GameObject::set_sprite(SpriteIndexes::enemy_sprite);
		GameObject::set_size(static_cast<float>(size_), static_cast<float>(size_));
		GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });
		GameObject::set_tag(Tags::Enemy);
	}

	Enemy::~Enemy()
	{
	}

	void Enemy::start_up()
	{
	}

	void Enemy::update()
	{
		{	//Dont remove used for live time of the velocity_mutex_
			std::unique_lock<std::mutex> lock(GameObject::velocity_modify_mutex);
			sf::Vector2f velocity = GameObject::get_velocity();
			GameObject::set_position(sf::Vector2f{ GameObject::get_position().x + (velocity.x * Time::delta_time()), GameObject::get_position().y + (velocity.y * Time::delta_time()) });
		}
		if (GameObject::get_position().x < 0.0f)
		{
			GameEngine::remove_game_object(this);
		}
		internal_timer += Time::delta_time();
		if (internal_timer > fire_rate_)
		{
			internal_timer -= fire_rate_;
			GameEngine::instantiate(new EnemyBullet(), GameObject::get_position());
		}

	}
}

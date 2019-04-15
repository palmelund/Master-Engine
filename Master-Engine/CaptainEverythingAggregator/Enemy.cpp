#include "pch.h"
#include "Enemy.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"
#include "../MasterEngineLibAggregator/GameEngine.h"
#include "EnemyBullet.h"
#include "../CaptainEverythingShared/SpriteIndexes.h"
#include "../CaptainEverythingShared/Constants.h"

namespace CaptainEverythingAggregator {
	using namespace CaptainEverythingShared;

	Enemy::Enemy(sf::Vector2f position) : GameObject(false)
	{
		size_ = ENEMY_SIZE;
		fire_rate_ = ENEMY_FIRE_RATE;
		internal_timer = 0;
		GameObject::set_velocity(sf::Vector2f{ -100.0f, 0.0f });
		GameObject::set_sprite(ENEMY_SPRITE);
		GameObject::set_size(static_cast<float>(size_), static_cast<float>(size_));
		GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });
		GameObject::set_tag(Tags::Enemy);
		GameObject::position_.set_vector(position);
	}

	Enemy::~Enemy()
	{
	}

	void Enemy::start_up()
	{
	}

	void Enemy::update()
	{
		sf::Vector2f velocity = GameObject::get_velocity();
		GameObject::position_ += sf::Vector2f{ (velocity.x * Time::delta_time()), (velocity.y * Time::delta_time()) };
		
		if (GameObject::get_position().x < 0.0f)
		{
			GameEngine::remove_game_object(this);
		}
		internal_timer += Time::delta_time();
		if (internal_timer > fire_rate_)
		{
			internal_timer -= fire_rate_;
			GameEngine::instantiate(new EnemyBullet(GameObject::get_position()));
		}

	}
}

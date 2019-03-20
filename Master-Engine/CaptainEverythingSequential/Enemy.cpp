#include "pch.h"
#include "Enemy.h"
#include "../MasterEngineLibSequential/ResourceManager.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"
#include "../MasterEngineLibSequential/GameEngine.h"
#include "EnemyBullet.h"
#include "../CaptainEverythingShared/SpriteIndexes.h"

namespace CaptainEverythingSequential {
	using namespace CaptainEverythingShared;
	using namespace MasterEngine::LibShared;
	Enemy::Enemy() : GameObject(false)
	{
		size_ = 20;
		GameObject::set_velocity(sf::Vector2f{ -100.0f, 0.0f });
		GameObject::set_sprite(ENEMY_SPRITE);
		GameObject::set_size(size_, size_);
		GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });
		fire_rate_ = 1.3;
		internal_timer = 0;
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
		internal_timer += Time::DeltaTime();
		sf::Vector2f velocity = GameObject::get_velocity();
		GameObject::set_position(sf::Vector2f{ GameObject::get_position().x + (velocity.x * Time::DeltaTime()), GameObject::get_position().y + (velocity.y * Time::DeltaTime()) });
		if (GameObject::get_position().x < 0.0f)
		{
			GameEngine::remove_game_object(this);
		}
		if (internal_timer > fire_rate_)
		{
			internal_timer -= fire_rate_;
			GameEngine::Instantiate(new EnemyBullet(), GameObject::get_position());
		}

	}
}

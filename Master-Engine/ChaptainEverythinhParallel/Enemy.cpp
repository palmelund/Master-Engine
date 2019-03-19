#include "pch.h"
#include "Enemy.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"
#include "../MasterEngineLibParallel/GameEngine.h"
#include "EnemyBullet.h"
#include "SpriteIndexes.h"
#include <mutex>

Enemy::Enemy() : GameObject(false)
{
	size_ = 20;
	fire_rate_ = 1.3;
	internal_timer = 0;
	GameObject::set_velocity(sf::Vector2f{ -100.0f, 0.0f });
	GameObject::set_sprite(ENEMY_SPRITE);
	GameObject::set_size(size_, size_);
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
		std::unique_lock<std::mutex> lock(velocity_mutex_);
		sf::Vector2f velocity = GameObject::get_velocity();
		GameObject::set_position(sf::Vector2f{ GameObject::get_position().x + (velocity.x*Time::DeltaTime()), GameObject::get_position().y + (velocity.y*Time::DeltaTime()) });
	}
	if (GameObject::get_position().x < 0.0f)
	{
		GameEngine::remove_game_object(this);
	}
	internal_timer += Time::DeltaTime();
	if(internal_timer > fire_rate_)
	{
		internal_timer -= fire_rate_;
		GameEngine::Instantiate(new EnemyBullet(), GameObject::get_position());
	}

}

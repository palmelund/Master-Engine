#include "pch.h"
#include "EnemyBullet.h"
#include "../MasterEngineLibAggregator/GameEngine.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"
#include "../CaptainEverythingShared/SpriteIndexes.h"
#include "../CaptainEverythingShared/Constants.h"

namespace CaptainEverythingAggregator {
	using namespace CaptainEverythingShared;

	EnemyBullet::EnemyBullet(sf::Vector2f position) : GameObject(false)
	{
		size_ = ENEMY_BULLET_SIZE;
		GameObject::set_velocity(sf::Vector2f{ -300.0f, 0.0f });
		GameObject::set_sprite(BULLET_SPRITE);
		GameObject::set_size(static_cast<float>(size_), static_cast<float>(size_));
		GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });
		GameObject::set_tag(Tags::EnemyBullet);
		GameObject::position_.set_vector(position);
	}


	EnemyBullet::~EnemyBullet()
	{
	}

	void EnemyBullet::start_up()
	{
	}

	void EnemyBullet::update()
	{
		sf::Vector2f velocity = GameObject::get_velocity();
		GameObject::position_ += (sf::Vector2f{ (velocity.x * Time::delta_time()), (velocity.y * Time::delta_time()) });
		
		if (GameObject::get_position().x < 0.0f)
		{
			GameEngine::remove_game_object(this);
		}
	}
}

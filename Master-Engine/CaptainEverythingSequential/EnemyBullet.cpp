#include "pch.h"
#include "EnemyBullet.h"
#include "../MasterEngineLibSequential/GameEngine.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"
#include "../CaptainEverythingShared/SpriteIndexes.h"
#include "../CaptainEverythingShared/Constants.h"

namespace CaptainEverythingSequential {
	using namespace CaptainEverythingShared;
	using namespace MasterEngine::LibShared;

	EnemyBullet::EnemyBullet() : GameObject(false)
	{
		size_ = Constants::enemy_bullet_size;
		GameObject::set_velocity(sf::Vector2f{ -300.0f, 0.0f });
		GameObject::set_sprite(SpriteIndexes::bullet_sprite);
		GameObject::set_size(static_cast<float>(size_), static_cast<float>(size_));
		GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });
		GameObject::set_tag(Tags::EnemyBullet);
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
		GameObject::set_position(sf::Vector2f{ GameObject::get_position().x + (velocity.x * Time::delta_time()), GameObject::get_position().y + (velocity.y * Time::delta_time()) });
		if (GameObject::get_position().x < 0.0f)
		{
			GameEngine::remove_game_object(this);
		}
	}
}

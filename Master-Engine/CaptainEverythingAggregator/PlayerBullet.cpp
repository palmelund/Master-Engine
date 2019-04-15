#include "pch.h"
#include "PlayerBullet.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"
#include "../MasterEngineLibAggregator/GameEngine.h"
#include "../MasterEngineLibAggregator/Renderer.h"
#include "../MasterEngineLibAggregator/Collider.h"
#include "Spawner.h"
#include "../CaptainEverythingShared/SpriteIndexes.h"
#include "../CaptainEverythingShared/Constants.h"

namespace CaptainEverythingAggregator {
	using namespace CaptainEverythingShared;

	PlayerBullet::PlayerBullet(sf::Vector2f position) : GameObject(true)
	{
		size_ = PLAYER_BULLET_SIZE;
		set_velocity(sf::Vector2f{ 300.0f, 0.0f });
		GameObject::set_sprite(BULLET_SPRITE);
		GameObject::set_size(static_cast<float>(size_), static_cast<float>(size_));
		GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });
		GameObject::set_tag(Tags::Bullet);
		GameObject::position_.set_vector(position);
	}


	PlayerBullet::~PlayerBullet()
	{

	}

	void PlayerBullet::update()
	{
		sf::Vector2f velocity = GameObject::get_velocity();
		GameObject::position_ += sf::Vector2f{ (velocity.x * Time::delta_time()), (velocity.y * Time::delta_time()) };

		if (GameObject::get_position().x > Renderer::get_window_size()->x)
		{
			GameEngine::remove_game_object(this);
		}
	}

	void PlayerBullet::on_collision(GameObject * collider)
	{
		switch (collider->get_tag())
		{
		case Tags::Enemy:
			Spawner::get_single_ton()->add_enemy_hit();
		case  Tags::EnemyBullet:
			GameEngine::remove_game_object(collider);
			GameEngine::remove_game_object(this);
			break;
		default:
			break;
		}
	}
}

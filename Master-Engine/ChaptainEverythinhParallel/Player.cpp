#include "pch.h"
#include "Player.h"
#include "../MasterEngineLibParallel/GameEngine.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"
#include "PlayerBullet.h"
#include "Spawner.h"
#include "../CaptainEverythingShared/SpriteIndexes.h"
#include "../CaptainEverythingShared/Constants.h"

namespace CaptainEverythingParallel {
	using namespace CaptainEverythingShared;

	Player::Player() : GameObject(true), internal_timer(0)
	{
		size_ = Constants::player_size;
		GameObject::set_sprite(SpriteIndexes::player_sprite);
		GameObject::set_size(static_cast<float>(size_), static_cast<float>(size_));
		GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });
		speed = Constants::player_speed;
		fire_rate_ = Constants::player_fire_rate;
	}


	Player::~Player() = default;

	void Player::start_up()
	{
	}

	void Player::update()
	{

		internal_timer += Time::delta_time();
		if (internal_timer > fire_rate_)
		{
			internal_timer -= fire_rate_;
			GameEngine::instantiate(new PlayerBullet(), GameObject::get_position());
		}


		float distance = 9999;
		GameObject* closes = nullptr;
		for (auto game_object : GameEngine::get_game_state())
		{
			if (game_object->get_tag() == Tags::Enemy && game_object->get_position().x < distance)
			{
				distance = game_object->get_position().x;
				closes = game_object;
			}
		}
		if (closes == nullptr)
		{
			return;
		}
		auto velocity = GameObject::get_velocity();
		if (closes->get_position().y > GameObject::get_position().y)
		{
			if (velocity.y < 0)
			{
				velocity.y /= 2;
			}
			velocity.y += speed * Time::delta_time();
		}

		if (closes->get_position().y < GameObject::get_position().y)
		{
			if (velocity.y > 0)
			{
				velocity.y /= 2;
			}
			velocity.y -= speed * Time::delta_time();
		}
		GameObject::set_position(sf::Vector2f{ GameObject::get_position().x + (velocity.x * Time::delta_time()), GameObject::get_position().y + (velocity.y * Time::delta_time()) });
		GameObject::set_velocity(velocity);
	}

	void Player::on_collision(GameObject * collider)
	{
		if (collider->get_tag() == Tags::Enemy || collider->get_tag() == Tags::EnemyBullet)
		{
			Spawner::get_single_ton()->add_player_hit();
			GameEngine::remove_game_object(collider);
		}
	}
}

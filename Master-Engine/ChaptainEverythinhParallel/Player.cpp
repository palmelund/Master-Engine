#include "pch.h"
#include "Player.h"
#include "../MasterEngineLibParallel/GameEngine.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"
#include "PlayerBullet.h"
#include "Spawner.h"
#include "../CaptainEverythingShared/SpriteIndexes.h"
#include "../CaptainEverythingShared/Constants.h"
#include "../MasterEngineLibShared/Input.h"
#include "../MasterEngineLibParallel/Renderer.h"

namespace CaptainEverythingParallel {
	using namespace CaptainEverythingShared;

	Player::Player() : GameObject(true), fire_rate_cooldown_(0)
	{
		size_ = Constants::player_size;
		GameObject::set_sprite(SpriteIndexes::player_sprite);
		GameObject::set_size(static_cast<float>(size_), static_cast<float>(size_));
		GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });
		speed = Constants::player_acceleration;
		fire_rate_ = Constants::player_fire_rate;
	}


	Player::~Player() = default;

	void Player::start_up()
	{
	}

	void Player::update()
	{
		fire_rate_cooldown_ += Time::delta_time();
		if (fire_rate_cooldown_ > fire_rate_ && Input::get_key_hold(sf::Keyboard::Key::Space))
		{
			fire_rate_cooldown_ = 0;
			GameEngine::instantiate(new PlayerBullet(), GameObject::get_position());
		}

		sf::Vector2f velocity = get_velocity();

		if (Input::get_key_hold(sf::Keyboard::Key::Q))
		{
			velocity.x = 0;
			velocity.y = 0;
		}

		if (Input::get_key_hold(sf::Keyboard::Key::W))
		{
			velocity.y -= speed * Time::delta_time();
		}
		else if (Input::get_key_hold(sf::Keyboard::Key::S))
		{
			velocity.y += speed * Time::delta_time();
		}

		if (Input::get_key_hold(sf::Keyboard::Key::A))
		{
			velocity.x -= speed * Time::delta_time();
		}
		else if (Input::get_key_hold(sf::Keyboard::Key::D))
		{
			velocity.x += speed * Time::delta_time();
		}

		sf::Vector2f position = get_position();
		position = position + velocity * Time::delta_time();

		const auto* window_size = Renderer::get_window_size();

		if (position.x < 0)
		{
			position.x = 0;
			velocity.x = 0;
		}
		else if (position.x >= window_size->x - Constants::player_size)
		{
			position.x = window_size->x - Constants::player_size;
			velocity.x = 0;
		}

		if (position.y < 0)
		{
			position.y = 0;
			velocity.y = 0;
		}
		else if (position.y >= window_size->y - Constants::player_size)
		{
			position.y = window_size->y - Constants::player_size;
			velocity.y = 0;
		}

		GameObject::set_position(position);
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

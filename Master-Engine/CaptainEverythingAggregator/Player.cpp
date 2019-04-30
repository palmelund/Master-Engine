#include "pch.h"
#include "Player.h"
#include "../MasterEngineLibAggregator/GameEngine.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"
#include "PlayerBullet.h"
#include "Spawner.h"
#include "../CaptainEverythingShared/SpriteIndexes.h"
#include "../CaptainEverythingShared/Constants.h"
#include "../MasterEngineLibAggregator/Renderer.h"
#include "../MasterEngineLibShared/Input.h"

namespace CaptainEverythingAggregator {
	using namespace CaptainEverythingShared;

	Player::Player(sf::Vector2f position) : GameObject(true), fire_rate_cooldown_(0)
	{
		size_ = Constants::player_size;
		GameObject::set_sprite(SpriteIndexes::player_sprite);
		GameObject::set_size(static_cast<float>(size_), static_cast<float>(size_));
		GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });
		speed = Constants::player_acceleration;
		fire_rate_ = Constants::player_fire_rate;
		GameObject::position_.set_vector(position);
	}


	Player::~Player()
	{
	}

	void Player::start_up()
	{
	}

	void Player::update()
	{
		fire_rate_cooldown_ += Time::delta_time();
		if (fire_rate_cooldown_ > fire_rate_ && Input::get_key_hold(sf::Keyboard::Key::Space))
		{
			fire_rate_cooldown_ = 0;
			GameEngine::instantiate(new PlayerBullet(GameObject::get_position()));
		}

		auto position = get_position();
		
		set_position(position + velocity_.get_vector() * Time::delta_time());

		sf::Vector2f velocity = sf::Vector2f();

		std::ostringstream ss;
		ss << "x: ";
		ss << velocity.x;
		ss << " y: ";
		ss << velocity.y;

		Renderer::draw_text(ss.str(), 100, 100, 14);

		if (Input::get_key_hold(sf::Keyboard::Key::Q))
		{
			velocity_.assign(sf::Vector2f{}, std::numeric_limits<int>::max());
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

		const auto* window_size = Renderer::get_window_size();

		bool clamped{ false };

		if (position.x < 0)
		{
			position.x = 0;
			velocity.x = 0;
			clamped = true;
		}
		else if (position.x >= window_size->x - Constants::player_size)
		{
			position.x = window_size->x - Constants::player_size;
			velocity.x = 0;
			clamped = true;
		}

		if (position.y < 0)
		{
			position.y = 0;
			velocity.y = 0;
			clamped = true;
		}
		else if (position.y >= window_size->y - Constants::player_size)
		{
			position.y = window_size->y - Constants::player_size;
			velocity.y = 0;
			clamped = true;
		}

		if(clamped)
		{
			position_.assign(position, std::numeric_limits<int>::max());
		}

		velocity_ += velocity;
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

#include "pch.h"
#include "Boss.h"
#include "../MasterEngineLibShared/Tags.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibSequential/Renderer.h"
#include "BossShield.h"
#include "../MasterEngineLibSequential/GameEngine.h"
#include "../CaptainEverythingShared/SpriteIndexes.h"
#include "../CaptainEverythingShared/Constants.h"

namespace CaptainEverythingSequential {
	using namespace CaptainEverythingShared;
	using namespace MasterEngine::LibShared;

	Boss::Boss() : GameObject(true)
	{
		size_ = Constants::boss_size;
		shield_amount_ = Constants::boss_shield_count;
		GameObject::set_velocity(sf::Vector2f{ 0.0f, 100.0f });
		GameObject::set_sprite(SpriteIndexes::boss_sprite);
		GameObject::set_size(static_cast<float>(size_), static_cast<float>(size_));
		GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });
		//GameObject::set_tag(Tags::Enemy);
	}


	Boss::~Boss()
	{
	}

	void Boss::start_up()
	{
		for (int i = 0; i < shield_amount_; i++)
		{
			new BossShield(this, i);
		}
	}

	void Boss::update()
	{
		sf::Vector2f velocity = GameObject::get_velocity();
		GameObject::set_position(sf::Vector2f{ GameObject::get_position().x + (velocity.x * Time::delta_time()), GameObject::get_position().y + (velocity.y * Time::delta_time()) });
		if (GameObject::get_position().y < 50)
		{
			velocity.y = 50;
		}
		if (GameObject::get_position().y > Renderer::get_window_size()->y - size_ - 50)
		{
			velocity.y = -50;
		}
		if (GameObject::get_position().x < Renderer::get_window_size()->x - size_ - 110 || GameObject::get_position().x > Renderer::get_window_size()->x - size_ - 90)
		{
			velocity.x = (Renderer::get_window_size()->x - size_ - 100) - (GameObject::get_position().x);
		}
		else
		{
			velocity.x = 0;
		}
		GameObject::set_velocity(velocity);
	}

	void Boss::on_collision(GameObject * collider)
	{
		if (collider->get_tag() == Tags::Bullet && shield_amount_ == 0)
		{
			GameEngine::remove_game_object(collider);
			GameEngine::remove_game_object(this);
		}

	}

	void Boss::loss_shield()
	{
		shield_amount_--;
	}
}

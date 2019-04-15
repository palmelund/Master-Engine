#include "pch.h"
#include "../MasterEngineLibShared/Tags.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibAggregator/Renderer.h"
#include "../MasterEngineLibAggregator/GameEngine.h"
#include "Boss.h"
#include "BossShield.h"
#include <mutex>
#include "../CaptainEverythingShared/SpriteIndexes.h"
#include "../CaptainEverythingShared/Constants.h"

namespace CaptainEverythingAggregator {
	using namespace CaptainEverythingShared;

	Boss::Boss(sf::Vector2f position) : GameObject(true)
	{
		size_ = BOSS_SIZE;
		shield_amount_ = BOSS_SHIELD_COUNT;
		GameObject::set_velocity(sf::Vector2f{ 0.0f, 100.0f });
		GameObject::set_sprite(BOSS_SPRITE);
		GameObject::set_size(static_cast<float>(size_), static_cast<float>(size_));
		GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });
		GameObject::position_.set_vector(position);
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
		std::unique_lock<std::mutex> lock(shield_amount_mutex_);//Very little chanche for ever happening but if the boss could not be killed
		shield_amount_--;
	}
}

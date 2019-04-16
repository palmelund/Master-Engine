#include "pch.h"
#include "BossShield.h"
#include "Boss.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"
#include "../MasterEngineLibAggregator/GameEngine.h"
#include "../CaptainEverythingShared/SpriteIndexes.h"
#include "../CaptainEverythingShared/Constants.h"

namespace CaptainEverythingAggregator {
	using namespace CaptainEverythingShared;

	const float M_PI = 3.14159265358979323846f;  /* pi */

	BossShield::BossShield(Boss* boss, int position) : GameObject(true)
	{
		circumference_ = M_PI * 2.0f * Constants::boss_shield_distance;
		position_ = (M_PI * 2.0f) * (static_cast<float>(position) / 3.0f);
		boss_ = boss;
		GameObject::set_sprite(SpriteIndexes::shield_sprite);
		GameObject::set_size(Constants::boss_shield_size, Constants::boss_shield_size);
		GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });

		position_ += (M_PI * 2) * (Time::delta_time() * Constants::boss_shield_speed) / circumference_;
		float posx = std::cos(position_) * Constants::boss_shield_distance;
		float posy = std::sin(position_) * Constants::boss_shield_distance;
		GameObject::position_.set_vector(sf::Vector2f{ boss_->get_position().x + posx, boss_->get_position().y + posy });
	}


	BossShield::~BossShield()
	{

	}

	void BossShield::update()
	{
		position_ += (M_PI * 2) * (Time::delta_time() * Constants::boss_shield_speed) / circumference_;
		float posx = std::cos(position_) * Constants::boss_shield_distance;
		float posy = std::sin(position_) * Constants::boss_shield_distance;
		GameObject::set_position(sf::Vector2f{ boss_->get_position().x + posx, boss_->get_position().y + posy });

	}

	void BossShield::on_collision(GameObject * collider)
	{
		if (collider->get_tag() == Tags::Bullet)
		{
			GameEngine::remove_game_object(this);
			boss_->loss_shield();
		}
	}
}

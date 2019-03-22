#include "pch.h"
#include "BossShield.h"
#include "Boss.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"
#include "../MasterEngineLibSequential/GameEngine.h"
#include "../CaptainEverythingShared/SpriteIndexes.h"
#include "../CaptainEverythingShared/Constants.h"

namespace CaptainEverythingSequential {
	using namespace CaptainEverythingShared;
	using namespace MasterEngine::LibShared;

	const float M_PI = 3.14159265358979323846f;  /* pi */

	BossShield::BossShield(Boss* boss, int position) : GameObject(true)
	{


		circumference_ = M_PI * 2.0f * BOSS_SHIELD_DISTANCE;
		position_ = (M_PI * 2.0f) * (static_cast<float>(position) / 3.0f);
		boss_ = boss;
		GameObject::set_sprite(SHIELD_SPRITE);
		GameObject::set_size(BOSS_SHIELD_SIZE, BOSS_SHIELD_SIZE);
		GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });
		//GameObject::set_tag(Tags::Enemy);
	}


	BossShield::~BossShield()
	{

	}

	void BossShield::update()
	{
		position_ += (M_PI * 2) * (Time::DeltaTime() * BOSS_SHIELD_SPEED) / circumference_;
		float posx = std::cos(position_) * BOSS_SHIELD_DISTANCE;
		float posy = std::sin(position_) * BOSS_SHIELD_DISTANCE;
		GameObject::set_position(sf::Vector2f{ boss_->get_position().x + posx, boss_->get_position().y + posy });

	}

	void BossShield::OnCollision(GameObject * collider)
	{
		if (collider->get_tag() == Tags::Bullet)
		{
			GameEngine::remove_game_object(this);
			boss_->loss_shield();
		}
	}
}

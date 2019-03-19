#include "pch.h"
#include "BossShield.h"
#include "Boss.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"
#include "../MasterEngineLibParallel/GameEngine.h"
#include "SpriteIndexes.h"

const float M_PI = 3.14159265358979323846f;  /* pi */
const float Boss_Distance = 75.0f;
const float Speed = 100.0f;
const float Size = 50.0f;

BossShield::BossShield(Boss* boss, int position) : GameObject(true)
{
	//No locks
	circumference_ = M_PI * 2.0f * Boss_Distance;
	position_ = (M_PI * 2.0f) * (static_cast<float>(position) / 3.0f);
	boss_ = boss;
	GameObject::set_sprite(SHIELD_SPRITE);
	GameObject::set_size(Size, Size);
	GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });
}


BossShield::~BossShield()
{
	
}

void BossShield::update()
{
	position_ += (M_PI * 2)*(Time::DeltaTime() * Speed) / circumference_;
	float posx = std::cos(position_)*Boss_Distance;
	float posy = std::sin(position_)*Boss_Distance;
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

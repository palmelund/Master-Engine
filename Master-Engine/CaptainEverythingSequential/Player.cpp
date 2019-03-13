#include "pch.h"
#include "Player.h"
#include "../MasterEngineLibSequential/ResourceManager.h"
#include "../MasterEngineLibSequential/GameEngine.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"
#include "PlayerBullet.h"
#include "Spawner.h"


Player::Player() : GameObject(false, true)
{
	size_ = 20;
	GameObject::set_sprite(ResourceManager::get_texture("player.png"));
	GameObject::set_size(size_, size_);
	GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, sf::Vector2f{sprite_.getLocalBounds().width, sprite_.getLocalBounds().height} });
	speed = 900;
	fire_rate_ = 0.3f;
}


Player::~Player()
{
}

void Player::start_up()
{
}

void Player::update()
{

	internal_timer += Time::DeltaTime();
	if (internal_timer > fire_rate_)
	{
		internal_timer -= fire_rate_;
		GameEngine::Instantiate(new PlayerBullet(), GameObject::get_position());
	}


	float distance = 9999;
	GameObject* closes = nullptr;
	for(GameObject* game_object : GameEngine::get_gamestate())
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
	sf::Vector2f velocity = M_Transform::get_velocity();
	if (closes->get_position().y > GameObject::get_position().y)
	{
		if (velocity.y < 0)
		{
			velocity.y /= 2;
		}
		velocity.y += speed*Time::DeltaTime();
	}

	if (closes->get_position().y < GameObject::get_position().y)
	{
		if (velocity.y > 0)
		{
			velocity.y /= 2;
		}
		velocity.y -= speed * Time::DeltaTime();
	}
	GameObject::set_position(sf::Vector2f{ GameObject::get_position().x + (velocity.x*Time::DeltaTime()), GameObject::get_position().y + (velocity.y*Time::DeltaTime()) });
	M_Transform::set_velocity(velocity);
}

void Player::OnCollision(GameObject * collider)
{
	if (collider->get_tag() == Tags::Enemy || collider->get_tag() == Tags::EnemyBullet)
	{
		Spawner::get_single_ton()->add_player_hit();
		GameEngine::remove_game_object(collider);
	}
}

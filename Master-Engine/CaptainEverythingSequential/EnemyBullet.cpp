#include "pch.h"
#include "EnemyBullet.h"
#include "../MasterEngineLibSequential/ResourceManager.h"
#include "../MasterEngineLibSequential/GameEngine.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"


EnemyBullet::EnemyBullet() : GameObject(false)
{
	size_ = 20;
	M_Transform::set_velocity(sf::Vector2f{ -300.0f, 0.0f });
	GameObject::set_sprite(ResourceManager::get_texture("bullet.png"));
	GameObject::set_size(size_, size_);
	GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, sf::Vector2f{sprite_.getLocalBounds().width, sprite_.getLocalBounds().height} });
	GameObject::set_tag(Tags::EnemyBullet);
}


EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::start_up()
{
}

void EnemyBullet::update()
{
	sf::Vector2f velocity = M_Transform::get_velocity();
	GameObject::set_position(sf::Vector2f{ GameObject::get_position().x + (velocity.x*Time::DeltaTime()), GameObject::get_position().y + (velocity.y*Time::DeltaTime()) });
	if (GameObject::get_position().x < 0.0f)
	{
		GameEngine::remove_game_object(this);
	}
}

#include "pch.h"
#include "PlayerBullet.h"
#include "../MasterEngineLibSequential/ResourceManager.h"
#include "../MasterEngineLibSequential/GameEngine.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"
#include "../MasterEngineLibSequential/Renderer.h"


PlayerBullet::PlayerBullet() : GameObject(false, true)
{
	size_ = 20;
	velocity = sf::Vector2f{ 300.0f, 0.0f };
	GameObject::set_sprite(ResourceManager::get_texture("bullet.png"));
	GameObject::set_size(size_, size_);
	GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, sf::Vector2f{sprite_.getLocalBounds().width, sprite_.getLocalBounds().height} });
}


PlayerBullet::~PlayerBullet()
{
	
}

void PlayerBullet::update()
{
	GameObject::set_position(sf::Vector2f{ GameObject::get_position().x + (velocity.x*Time::DeltaTime()), GameObject::get_position().y + (velocity.y*Time::DeltaTime()) });
	if (GameObject::get_position().x > Renderer::get_window_size()->x)
	{
		GameEngine::remove_game_object(this);
	}
}

void PlayerBullet::OnCollision(GameObject * collider)
{
	if (collider->get_tag() == Tags::Enemy || collider->get_tag() == Tags::EnemyBullet)
	{
		GameEngine::remove_game_object(collider);
		GameEngine::remove_game_object(this);
	}
}

#include "pch.h"
#include "Boss.h"
#include "../MasterEngineLibSequential/ResourceManager.h"
#include "../MasterEngineLibShared/Tags.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibSequential/Renderer.h"
#include "BossShield.h"
#include "../MasterEngineLibSequential/GameEngine.h"
#include "M_Transform.h"

Boss::Boss() : GameObject(false, true), M_Transform()
{
	size_ = 50;
	shield_amount_ = 3;
	M_Transform::set_velocity(sf::Vector2f{ 0.0f, 100.0f });
	GameObject::set_sprite(ResourceManager::get_texture("boss.png"));
	GameObject::set_size(size_, size_);
	GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, sf::Vector2f{sprite_.getLocalBounds().width, sprite_.getLocalBounds().height} });
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
	sf::Vector2f velocity = M_Transform::get_velocity();
	GameObject::set_position(sf::Vector2f{ GameObject::get_position().x + (velocity.x*Time::DeltaTime()), GameObject::get_position().y + (velocity.y*Time::DeltaTime()) });
	if (GameObject::get_position().y < 50)
	{
		velocity.y = 50;
	}
	if (GameObject::get_position().y > Renderer::get_window_size()->y - size_ -50)
	{
		velocity.y = -50;
	}
	if (GameObject::get_position().x < Renderer::get_window_size()->x - size_ - 110 || GameObject::get_position().x > Renderer::get_window_size()->x - size_ - 90)
	{
		velocity.x =   (Renderer::get_window_size()->x - size_ - 100)- (GameObject::get_position().x) ;
	}
	else
	{
		velocity.x = 0;
	}
	M_Transform::set_velocity(velocity);
}

void Boss::OnCollision(GameObject * collider)
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

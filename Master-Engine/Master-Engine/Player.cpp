#include "pch.h"
#include "Player.h"
#include "Time.h"
#include "Input.h"
#include  "ResourceManager.h"
#include "Renderer.h"
#include <algorithm>

Player::Player(const std::string& texture) : GameObject(true)
{
	size_ = 20;
	velocity = sf::Vector2f{ 100.0, 100.0};
	GameObject::set_sprite(ResourceManager::get_texture(texture));
	GameObject::set_size(size_, size_);
	GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, sf::Vector2f{sprite_.getLocalBounds().width, sprite_.getLocalBounds().height} });
}


Player::~Player()
{
}

void Player::update()
{
	sf::Vector2f newVector = sf::Vector2f{ 0, 0};
	if (Input::get_key_hold(KeyCode::key_w))
	{
		newVector.y = -50;
	}
	else if (Input::get_key_hold(KeyCode::key_s))
	{
		newVector.y = 50;
	}

	if (Input::get_key_hold(KeyCode::key_a))
	{
		newVector.x = -50;
	}
	else if (Input::get_key_hold(KeyCode::key_d))
	{
		newVector.x = 50;
	}
	velocity = newVector;

	if (GameObject::get_position().x > Renderer::get_window_size()->x - size_ || GameObject::get_position().x < 0)
	{
		GameObject::set_position(sf::Vector2f{Player::clamp( GameObject::get_position().x, 1.0f, Renderer::get_window_size()->x - size_-1.0f) , GameObject::get_position().y });
		velocity.x = 0;
	}
	if (GameObject::get_position().y > Renderer::get_window_size()->y - size_ || GameObject::get_position().y < 0)
	{
		GameObject::set_position(sf::Vector2f{ GameObject::get_position().x ,Player::clamp(GameObject::get_position().y, 1.0f, Renderer::get_window_size()->y - size_ - 1.0f) });
		velocity.y = 0;
	}
	GameObject::set_position(sf::Vector2f{ GameObject::get_position().x + (velocity.x*Time::DeltaTime()), GameObject::get_position().y + (velocity.y*Time::DeltaTime()) });

}

void Player::OnCollision(GameObject * collider)
{
	if(collider->get_tag() == Tags::Enemy)
	{
		GameObject::set_position(sf::Vector2f{ GameObject::get_position().x + (velocity.x*Time::DeltaTime()*-1.2f), GameObject::get_position().y + (velocity.y*Time::DeltaTime()*-1.2f) });
	}

}

sf::Vector2f Player::rotate_vector(sf::Vector2f vector2)
{
	float theta = 90.0 * 4.0 * atan(1.0) / 180.0;

	float cs = cos(theta);
	float sn = sin(theta);

	float nx = vector2.x * cs - vector2.y * sn;
	float ny = vector2.x * sn + vector2.y * cs;
	return sf::Vector2f(nx,ny);
}


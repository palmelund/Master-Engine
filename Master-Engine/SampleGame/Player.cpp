#include "pch.h"
#include "Player.h"
#include "../MasterEngineLibSequential/ResourceManager.h"
#include "../MasterEngineLibShared/Input.h"
#include "../MasterEngineLibSequential/Renderer.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"
#include <sstream>

Player::Player(const std::string& texture) : GameObject(true)
{
	size_ = 20;
	velocity = sf::Vector2f{ 100.0, 100.0};
	GameObject::set_sprite(ResourceManager::get_texture(texture));
	GameObject::set_size(static_cast<float>(size_), static_cast<float>(size_));
	GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, sf::Vector2f{sprite_.getLocalBounds().width, sprite_.getLocalBounds().height} });
}


Player::~Player()
{
}

void Player::update()
{
	sf::Vector2f newVector = sf::Vector2f{ 0, 0};
	if (Input::get_key_hold(sf::Keyboard::W))
	{
		newVector.y = -50;
	}
	else if (Input::get_key_hold(sf::Keyboard::S))
	{
		newVector.y = 50;
	}

	if (Input::get_key_hold(sf::Keyboard::A))
	{
		newVector.x = -50;
	}
	else if (Input::get_key_hold(sf::Keyboard::D))
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

	const auto n_pos = get_position();

	std::ostringstream ss;
	ss << "x: ";
	ss << n_pos.x;
	ss << " y: ";
	ss << n_pos.y;

	Renderer::draw_text(ss.str(),10,10,24);
}

void Player::OnCollision(GameObject * collider)
{
	if(collider->get_tag() == Tags::Enemy)
	{
		GameObject::set_position(sf::Vector2f{ GameObject::get_position().x + (velocity.x*Time::DeltaTime()*-1.2f), GameObject::get_position().y + (velocity.y*Time::DeltaTime()*-1.2f) });
	}

}
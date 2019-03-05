#include "pch.h"
#include "Player.h"
#include "Time.h"


Player::Player() : GameObject(true)
{
	velocity = sf::Vector2f{ 50.0,50.0 };
}


Player::~Player()
{
}

void Player::update()
{
	GameObject::set_position(sf::Vector2f{ GameObject::get_position().x + (velocity.x*Time::DeltaTime()), GameObject::get_position().y + (velocity.y*Time::DeltaTime() )});
	if (GameObject::get_position().x > 400-10)
	{
		velocity.x = -50;
	}
	else if (GameObject::get_position().x < 0)
	{
		velocity.x = 50;
	}
	if (GameObject::get_position().y > 300-10)
	{
		velocity.y = -50;
	}
	else if (GameObject::get_position().y < 0)
	{
		velocity.y = 50;
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

#include "pch.h"
#include <SFML/System/Vector2.hpp>
#include "M_Transform.h"


M_Transform::M_Transform()
{
	velocity_ = sf::Vector2f{ 0,0 };
}


M_Transform::~M_Transform()
{
}

void M_Transform::add_velocity(sf::Vector2f force)
{
	velocity_ = sf::Vector2f{ velocity_.x + force.x, velocity_.y + force.y };
}

void M_Transform::set_velocity(sf::Vector2f velocity)
{
	velocity_ = velocity;
}

sf::Vector2f M_Transform::get_velocity()
{
	return velocity_;
}

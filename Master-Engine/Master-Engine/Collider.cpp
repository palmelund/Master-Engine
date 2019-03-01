#include "pch.h"
#include "Collider.h"
#include "SFML/Graphics.hpp"
#include "GameState.h"

Collider::Collider(sf::Vector2f localPosition, sf::Vector2f size)
{
	LocalPosition = localPosition;
	Size = size;
}

Collider::~Collider()
{
}

Transform Collider::get_collider()
{
	Transform myTransform{};
	sf::Vector2f owner_pos = owner_->get_position();
	myTransform.posX = LocalPosition.x + owner_pos.x;
	myTransform.posY = LocalPosition.y + owner_pos.y;
	myTransform.sizeX = Size.x*owner_->get_scale();
	myTransform.sizeY = Size.y*owner_->get_scale();
	return myTransform;
}

void Collider::collision_check()
{
	for (GameObject* colliders : GameState::get_gamestate()) {
		for (Collider* collider : colliders->get_colliders()) {
			if(ColliderOverLap(get_collider(), collider->get_collider()))
			owner_->OnCollision(colliders);
		}
	}
}

bool Collider::ColliderOverLap(Transform object1, Transform Object2)
{
	float l1x = object1.posX;
	float l1y = object1.posY;
	float r1x = object1.posX + object1.sizeX;
	float r1y = object1.posY - object1.sizeY;
	float l2x = Object2.posX;
	float l2y = Object2.posY;
	float r2x = Object2.posX + Object2.sizeX;
	float r2y = Object2.posY - Object2.sizeY;

	// If one rectangle is on left side of other 
	if (l1x > r2x || l2x > r1x) {
		return false;
	}

	// If one rectangle is above other 
	if (l1y < r2y || l2y < r1y) {

		return false;
	}

	return true;
}

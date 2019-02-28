#include "pch.h"
#include "Collider.h"
#include "GameState.h"





Collider::Collider(sf::Vector2f localPosition, sf::Vector2f size, GameObject* owner)
{
	Owner = owner;
	LocalPosition = localPosition;
	Size = size;
}

Collider::~Collider()
{
}

Transform Collider::GetCollider()
{
	Transform myTransform{};
	myTransform.posX = LocalPosition[0] + Owner->
	return ;
}

void Collider::CollisionCheck()
{
	for (auto* colliders : GameState::game_objects_) {

	}
}

bool Collider::ColliderOverLap(Transform obejct1, Transform Object2)
{
	return false;
}

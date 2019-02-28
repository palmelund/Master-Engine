#pragma once
#include <SFML/Graphics.hpp>
#include"GameObject.h"
#include "Transform.h"
class Collider
{
public:
	Collider(sf::Vector2f localPosition, sf::Vector2f size, GameObject *owner);
	~Collider();
	sf::Vector2f LocalPosition;
	sf::Vector2f Size;

	GameObject *Owner;

	Transform GetCollider();
	void CollisionCheck();

private:
	bool ColliderOverLap(Transform obejct1, Transform Object2);
	
};


#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Transform.h"

class  GameObject;

class Collider
{
public:
	Collider(sf::Vector2f localPosition, sf::Vector2f size);
	~Collider();
	sf::Vector2f LocalPosition;
	sf::Vector2f Size;

	Transform get_collider();

	static bool ColliderOverLap(Transform object1, Transform Object2);

private:
	GameObject* owner_;
	
};

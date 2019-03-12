#pragma once
#include "G:\Git\Master-Engine\Master-Engine\MasterEngineLibSequential\GameObject.h"
class BackgroundElement :
	public GameObject
{
public:
	BackgroundElement();
	~BackgroundElement();

	void update() override;
	void OnCollision(GameObject* collider) override;

	sf::Vector2f velocity;

private:
	int size_;
};


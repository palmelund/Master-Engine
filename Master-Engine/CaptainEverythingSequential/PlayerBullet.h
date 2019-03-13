#pragma once
#include "../MasterEngineLibSequential/GameObject.h"

class PlayerBullet :
	public GameObject
{
public:
	PlayerBullet();
	~PlayerBullet();

	void update() override;
	void OnCollision(GameObject* collider) override;

	sf::Vector2f velocity;

private:
	int size_;
};


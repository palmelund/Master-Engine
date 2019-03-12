#pragma once
#include "../MasterEngineLibSequential/GameObject.h"


class Player :
	public GameObject
{
public:
	Player();
	~Player();

	void start_up() override;
	void update() override;
	void OnCollision(GameObject* collider) override;
	sf::Vector2f velocity;

private:
	int size_;
	float fire_rate_;
	float internal_timer;
	float speed;
};


#pragma once
#include "../MasterEngineLibSequential/GameObject.h"
#include "M_Transform.h"


class Player :
	public GameObject, M_Transform
{
public:
	Player();
	~Player();

	void start_up() override;
	void update() override;
	void OnCollision(GameObject* collider) override;

private:
	int size_;
	float fire_rate_;
	float internal_timer;
	float speed;
};


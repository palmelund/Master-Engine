#pragma once
#include "../MasterEngineLibSequential/GameObject.h"
#include "M_Transform.h"

class Enemy :
	public GameObject, M_Transform
{
public:
	Enemy(std::string);
	~Enemy();

	void start_up() override;
	void update() override;

private:
	int size_;
	float fire_rate_;
	float internal_timer;

};


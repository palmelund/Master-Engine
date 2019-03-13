#pragma once
#include "../MasterEngineLibSequential/GameObject.h"

class Enemy :
	public GameObject
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


#pragma once
#include "G:\Git\Master-Engine\Master-Engine\MasterEngineLibSequential\GameObject.h"
class Spawner :
	public GameObject
{
public:
	Spawner();
	~Spawner();

	void start_up() override;
	void update() override;
private:
	float internal_timer;
	float spawn_time;
	float spawn_position_;
};


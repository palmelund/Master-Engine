#pragma once
#include "../MasterEngineLibSequential/GameObject.h"

class Boss;

class BossShield :
	public GameObject
{
public:
	BossShield(Boss*, int);
	~BossShield();

	void update() override;
	void OnCollision(GameObject* collider) override;
private:
	Boss* boss_;
	float position_;
	float circumference_;

};


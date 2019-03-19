#pragma once
#include "../MasterEngineLibParallel/GameObject.h"
#include <mutex>

class BackgroundElement :
	public GameObject
{
public:
	BackgroundElement();
	~BackgroundElement();

	void update() override;
	void OnCollision(GameObject* collider) override;

private:
	int size_;
};


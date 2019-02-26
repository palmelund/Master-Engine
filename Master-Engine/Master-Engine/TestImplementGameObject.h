#pragma once
#include "GameObject.h"
#include "RenderableObject.h"

class TestImplementGameObject final : public GameObject , public RenderableObject
{
public:
	TestImplementGameObject();
	~TestImplementGameObject();
};


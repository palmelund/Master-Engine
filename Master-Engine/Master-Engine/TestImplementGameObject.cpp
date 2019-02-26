#include "pch.h"
#include "TestImplementGameObject.h"


TestImplementGameObject::TestImplementGameObject() : GameObject(true), RenderableObject(wrapped_value<GameObject&>(*this))
{
}


TestImplementGameObject::~TestImplementGameObject()
{
}
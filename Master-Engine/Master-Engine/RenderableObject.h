#pragma once
#include "GameObject.h"
#include "WrappedValue.h"

class RenderableObject
{
public:

	explicit RenderableObject(wrapped_value<GameObject&> wrapped_game_object);

protected:
	~RenderableObject();

private:
	const GameObject& game_object_;
};


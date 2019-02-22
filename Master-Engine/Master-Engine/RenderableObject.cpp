#include "pch.h"
#include "RenderableObject.h"


RenderableObject::RenderableObject(wrapped_value<GameObject&> wrapped_game_object) : game_object_(wrapped_game_object.get())
{

}


RenderableObject::~RenderableObject()
{
}

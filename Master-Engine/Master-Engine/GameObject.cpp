#include "pch.h"
#include "GameObject.h"


GameObject::GameObject(bool requires_input)
{

}


GameObject::~GameObject()
{
}

bool GameObject::requires_input() const noexcept
{
	return requires_input_;
}

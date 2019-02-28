#include "pch.h"
#include "GameObject.h"
#include "GameEngine.h"
#include "Renderer.h"
#include "GameState.h"


GameObject::GameObject(const bool requires_input) : requires_input_(requires_input), id_(GameState::get_new_id())
{
	GameState::add_game_object(this);
}


void GameObject::unset_sprite()
{
	if(draw_)
	{
		Renderer::remove_sprite(sprite_);
		draw_ = false;
	}
}

std::vector<Collider*>& GameObject::get_colliders()
{
	// TODO: insert return statement here
	return colliders_;
}

GameObject::~GameObject()
{
	GameState::remove_game_object(this);
	unset_sprite();
}

bool GameObject::requires_input() const noexcept
{
	return requires_input_;
}

unsigned long long GameObject::get_id() const noexcept
{
	return id_;
}

void GameObject::set_sprite(sf::Texture& texture)
{
	sprite_.setTexture(texture);
	if(!draw_)
	{
		Renderer::add_sprite(sprite_);
		draw_ = true;
	}
}

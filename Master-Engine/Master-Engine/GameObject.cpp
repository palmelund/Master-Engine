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

void GameObject::add_collider(Collider& collider)
{
}

std::vector<Collider*>& GameObject::get_colliders()
{
	// TODO: insert return statement here
	return colliders_;
}

void GameObject::set_position(sf::Vector2f)
{
}

sf::Vector2f GameObject::get_position()
{
	return sf::Vector2f{};
}

Tags GameObject::get_tag()
{
	return Tags{};
}

float GameObject::get_scale()
{
	return  0.0f;
}

void GameObject::set_scale(float)
{
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

void GameObject::start_up()
{
}

void GameObject::update()
{
}

void GameObject::OnCollision(GameObject* collider)
{
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

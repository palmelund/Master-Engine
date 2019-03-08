#include "pch.h"
#include "GameObject.h"
#include "GameEngine.h"
#include "Renderer.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>


GameObject::GameObject(const bool requires_input) : requires_input_(requires_input), id_(GameState::get_new_id())
{
	draw_ = false;
	position_ = sf::Vector2f{ 0, 0};
	GameState::add_game_object(this);
}

GameObject::~GameObject()
{
	GameState::get_gamestate().erase(this);
	unset_sprite();
	for (Collider* collider : colliders_)
	{
		delete collider;
	}
}


void GameObject::unset_sprite()
{
	if(draw_)
	{
		Renderer::remove_sprite(sprite_);
		draw_ = false;
	}
}

void GameObject::add_collider(Collider* collider)
{
	collider->set_owner(this);
	colliders_.emplace_back(collider);
}

std::vector<Collider*>& GameObject::get_colliders()
{
	return colliders_;
}

void GameObject::set_position(sf::Vector2f newposition)
{
	
	position_ = newposition;
	sprite_.setPosition(newposition);
}

sf::Vector2f GameObject::get_position()
{
	return position_;
}

Tags GameObject::get_tag()
{
	return tag_;
}

float GameObject::get_width_scale()
{
	return width_scale_;
}

float GameObject::get_height_scale()
{
	return height_scale_;
}

void GameObject::set_scale(float h_scale, float w_scale)
{
	height_scale_ = h_scale;
	width_scale_ = w_scale;
	sprite_.setScale(sf::Vector2f{ h_scale, w_scale });
}

void GameObject::set_size(float width, float height)
{
	sf::IntRect rect = sprite_.getTextureRect();
	height_scale_ = width/rect.height;
	width_scale_ = height/rect.width;
	sprite_.setScale(sf::Vector2f{ height_scale_, width_scale_ });
}

void GameObject::set_tag(Tags tag)
{
	tag_ = tag;
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
		Renderer::add_sprite(&sprite_);
		draw_ = true;
	}
}

void GameObject::collision_check()
{
	for (GameObject* colliders : GameState::get_gamestate()) {
		Collider* collisiondetected = nullptr;
		for (Collider* myCollider : get_colliders()) {
			for (Collider* collider : colliders->get_colliders()) {
				if (Collider::ColliderOverLap(myCollider->get_collider(), collider->get_collider()))
				{
					collisiondetected = collider;
					break;
				}
			}
			if (collisiondetected != nullptr)
			{
				OnCollision(collisiondetected->get_owner());
				break;
			}
		}

		
	}
}

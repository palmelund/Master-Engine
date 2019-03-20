#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include "GameEngine.h"
#include "../MasterEngineLibShared/Tags.h"

namespace MasterEngine {
	namespace LibSequential {
		using namespace LibShared;

		GameObject::GameObject(const bool collision_code)
			: sprite_pos_(-1), collision_code_(collision_code), id_(GameEngine::get_new_id()),
			velocity_(sf::Vector2f{ 0, 0 }), tag_(Tags::Default), size_(Renderer::get_sprite_size())
		{
			GameEngine::add_game_object(this);
			if (collision_code)
			{
				GameEngine::add_collider(this);
			}
		}

		GameObject::~GameObject()
		{
			GameEngine::get_gamestate().erase(this);
			unset_sprite();
			for (Collider* collider : colliders_)
			{
				delete collider;
			}
			if (collision_code_)
			{
				GameEngine::remove_collider(this);
			}
		}


		void GameObject::unset_sprite()
		{
			if (draw_)
			{
				Renderer::remove_drawable_object(this);
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
		}

		sf::Vector2f GameObject::get_position()
		{
			return position_;
		}

		Tags GameObject::get_tag()
		{
			return tag_;
		}


		float GameObject::get_width_size()
		{
			return size_.x* width_scale_;
		}

		float GameObject::get_height_size()
		{
			return size_.y* height_scale_;
		}

		void GameObject::set_scale(float h_scale, float w_scale)
		{
			height_scale_ = h_scale;
			width_scale_ = w_scale;
		}

		void GameObject::set_size(float width, float height)
		{
			height_scale_ = width / size_.y;
			width_scale_ = height / size_.x;
		}

		void GameObject::set_tag(LibShared::Tags tag)
		{
			tag_ = tag;
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

		void GameObject::set_sprite(int sprite_position)
		{
			sprite_pos_ = sprite_position;
			if (!draw_)
			{
				Renderer::add_drawable_object(this);
				draw_ = true;
			}
		}

		void GameObject::collision_check()
		{
			for (GameObject* colliders : GameEngine::get_gamestate()) {
				GameObject* collisiondetected = nullptr;
				if (this == colliders)
				{
					continue;
				}
				for (Collider* myCollider : get_colliders()) {
					for (Collider* collider : colliders->get_colliders()) {
						if (Collider::ColliderOverLap(myCollider->get_collider(), collider->get_collider()))
						{
							collisiondetected = colliders;
							break;
						}
					}
					if (collisiondetected != nullptr)
					{
						OnCollision(collisiondetected);
						break;
					}
				}
			}
		}

		void GameObject::add_velocity(sf::Vector2f force)
		{
			velocity_ = sf::Vector2f{ velocity_.x + force.x, velocity_.y + force.y };
		}

		void GameObject::set_velocity(sf::Vector2f velocity)
		{
			velocity_ = velocity;
		}

		sf::Vector2f GameObject::get_scaled_size() const
		{
			return { size_.x * width_scale_, size_.y * height_scale_ };
		}

		sf::Vector2f GameObject::get_velocity()
		{
			return velocity_;
		}

		int GameObject::sprite_pos() const noexcept
		{
			return sprite_pos_;
		}
	}
}
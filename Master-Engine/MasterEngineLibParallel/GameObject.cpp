#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"
#include "GameEngine.h"
#include "../MasterEngineLibShared/Tags.h"
#include <mutex>

namespace MasterEngine {
	namespace LibParallel {

		using namespace LibShared;

		GameObject::GameObject(const bool enable_collisions)
			: sprite_pos_(-1), velocity_(sf::Vector2f{ 0, 0 }), enable_collisions_(enable_collisions),
			id_(GameEngine::get_new_id()), tag_(Tags::Default), size_(Renderer::get_sprite_size())
		{
			GameEngine::add_game_object(this);
			if (enable_collisions)
			{
				GameEngine::add_collider(this);
			}
		}

		GameObject::~GameObject()
		{
			auto& state = GameEngine::get_game_state();
			state.erase(std::find(state.begin(), state.end(), this));
			unset_sprite();
			for (auto collider : colliders_)
			{
				delete collider;
			}
			if (enable_collisions_)
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
			std::unique_lock<std::mutex> lock(collider_modify_mutex_);
			collider->set_owner(this);
			colliders_.emplace_back(collider);
		}

		std::vector<Collider*>& GameObject::get_colliders()
		{
			return colliders_;
		}

		void GameObject::set_position(const sf::Vector2f position)
		{

			position_ = position;
		}

		sf::Vector2f GameObject::get_position() const
		{
			return position_;
		}

		Tags GameObject::get_tag() const
		{
			return tag_;
		}


		float GameObject::get_width_size() const
		{
			return size_.x* width_scale_;
		}

		float GameObject::get_height_size() const
		{
			return size_.y* height_scale_;
		}

		void GameObject::set_scale(const float h_scale, const float w_scale)
		{
			height_scale_ = h_scale;
			width_scale_ = w_scale;
		}

		void GameObject::set_size(const float width, const float height)
		{
			height_scale_ = width / size_.y;
			width_scale_ = height / size_.x;
		}

		void GameObject::set_tag(const Tags tag)
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

		void GameObject::on_collision(GameObject* collider)
		{
		}

		void GameObject::set_sprite(const int sprite_position)
		{
			sprite_pos_ = sprite_position;
			if (!draw_)
			{
				Renderer::add_drawable_object(this);
				draw_ = true;
			}
		}

		// TODO: fixme
		void GameObject::collision_check()
		{
			for (auto potential_colliding_game_object : GameEngine::get_game_state()) {
				GameObject* colliding_game_object = nullptr;
				if (this == potential_colliding_game_object)
				{
					continue;
				}
				for (auto colliders : get_colliders()) {
					for (auto potential_colliders : potential_colliding_game_object->get_colliders()) {
						if (Collider::collider_overlap(colliders->get_collider(), potential_colliders->get_collider()))
						{
							colliding_game_object = potential_colliding_game_object;
							break;
						}
					}
					if (colliding_game_object != nullptr)
					{
						on_collision(colliding_game_object);
						break;
					}
				}
			}
		}

		void GameObject::add_velocity(const sf::Vector2f force)
		{
			velocity_ = sf::Vector2f{ velocity_.x + force.x, velocity_.y + force.y };
		}

		void GameObject::set_velocity(const sf::Vector2f velocity)
		{
			velocity_ = velocity;
		}

		sf::Vector2f GameObject::get_scaled_size() const
		{
			return { size_.x * width_scale_, size_.y * height_scale_ };
		}

		sf::Vector2f GameObject::get_velocity() const
		{
			return velocity_;
		}

		int GameObject::sprite_pos() const noexcept
		{
			return sprite_pos_;
		}
	}
}
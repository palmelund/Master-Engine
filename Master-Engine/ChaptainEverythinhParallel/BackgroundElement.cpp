#include "pch.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"
#include "../MasterEngineLibParallel/Renderer.h"
#include "BackgroundElement.h"
#include "../CaptainEverythingShared/SpriteIndexes.h"
#include "../CaptainEverythingShared/Constants.h"

namespace CaptainEverythingParallel {
	using namespace CaptainEverythingShared;
	using namespace MasterEngine::LibShared;

	BackgroundElement::BackgroundElement() : GameObject(true)
	{
		size_ = Constants::background_element_size;
		GameObject::set_velocity(sf::Vector2f{ 50.0f, -90.0f });
		GameObject::set_sprite(SpriteIndexes::background_sprite);
		GameObject::set_size(static_cast<float>(size_), static_cast<float>(size_));
		GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });
		GameObject::set_tag(Tags::Background);
	}


	BackgroundElement::~BackgroundElement()
	{

	}

	void BackgroundElement::update()
	{
		std::unique_lock<std::mutex> lock(GameObject::velocity_modify_mutex);
		sf::Vector2f position = GameObject::get_position();
		sf::Vector2f velocity = GameObject::get_velocity();
		GameObject::set_position(sf::Vector2f{ position.x + (velocity.x * Time::delta_time()), position.y + (velocity.y * Time::delta_time()) });
		position = GameObject::get_position();
		if (position.x < 0)
		{
			velocity.x = std::abs(velocity.x);
		}
		else if (position.x > Renderer::get_window_size()->x - size_)
		{
			velocity.x = -1 * std::abs(velocity.x);
		}
		if (position.y < 0)
		{
			velocity.y = std::abs(velocity.y);
		}
		else if (position.y > Renderer::get_window_size()->y - size_)
		{
			velocity.y = -1 * std::abs(velocity.y);
		}
		GameObject::set_velocity(velocity);

	}

	void BackgroundElement::on_collision(GameObject * collider)
	{
		if (collider->get_tag() == Tags::Background)
		{
			std::unique_lock<std::mutex> lock(GameObject::velocity_modify_mutex);
			sf::Vector2f position = GameObject::get_position();
			sf::Vector2f col_position = collider->get_position();
			sf::Vector2f velocity = GameObject::get_velocity();
			sf::Vector2f relative_position = sf::Vector2f{ (position.x + (size_ / 2)) - (col_position.x + (collider->get_width_size() / 2)),(position.y + (size_ / 2)) - (col_position.y + (collider->get_height_size() / 2)) };

			if (std::abs(relative_position.x) > std::abs(relative_position.y))
			{
				if (relative_position.x > 0)
				{
					velocity.x = std::abs(velocity.x);
				}
				else
				{
					velocity.x = -1 * std::abs(velocity.x);
				}

			}
			else
			{
				if (relative_position.y > 0)
				{
					velocity.y = std::abs(velocity.y);
				}
				else
				{
					velocity.y = -1 * std::abs(velocity.y);
				}
			}
			GameObject::set_velocity(velocity);
		}
	}
}

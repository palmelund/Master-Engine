#include "pch.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"
#include "../MasterEngineLibAggregator/Renderer.h"
#include "BackgroundElement.h"
#include "../CaptainEverythingShared/SpriteIndexes.h"
#include "../CaptainEverythingShared/Constants.h"
#include "SFML/Graphics.hpp"

namespace CaptainEverythingAggregator {
	using namespace CaptainEverythingShared;
	using namespace MasterEngine::LibShared;

	BackgroundElement::BackgroundElement() : GameObject(true)
	{
		size_ = BACKGROUND_ELEMENT_SIZE;
		GameObject::set_velocity(sf::Vector2f{ 50.0f, -90.0f });
		GameObject::set_sprite(BACKGROUND_SPRITE);
		GameObject::set_size(static_cast<float>(size_), static_cast<float>(size_));
		GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });
		GameObject::set_tag(Tags::Background);
	}


	BackgroundElement::~BackgroundElement()
	{

	}

	void BackgroundElement::update()
	{
		sf::Vector2f position = GameObject::get_position();
		sf::Vector2f velocity = GameObject::get_velocity();
		GameObject::set_position(sf::Vector2f{ position.x + (velocity.x * Time::DeltaTime()), position.y + (velocity.y * Time::DeltaTime()) });
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

	void BackgroundElement::OnCollision(GameObject * collider)
	{
		if (collider->get_tag() == Tags::Background)
		{
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
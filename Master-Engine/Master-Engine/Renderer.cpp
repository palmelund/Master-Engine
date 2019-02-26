#include "pch.h"
#include "Renderer.h"

std::unordered_set<const sf::Sprite*> Renderer::sprites_{};
sf::RenderWindow Renderer::window_{};

void Renderer::init(std::string window_name, int width, int height)
{
	const auto& v2 = sf::Vector2u(width, height);
	window_.setSize(v2);  // = sf::RenderWindow{ sf::VideoMode(width, height), window_name };
	window_.setTitle(window_name);
}

void Renderer::render()
{
	window_.clear(sf::Color::Black);
	for (auto& sprite : sprites_)
	{
		window_.draw(*sprite);
	}

	window_.display();
}

void Renderer::add_sprite(const sf::Sprite& sprite)
{
	const auto ptr = &sprite;
	sprites_.insert(ptr);
}

void Renderer::remove_sprite(const sf::Sprite& sprite)
{
	const auto ptr = &sprite;
	sprites_.erase(ptr);
}

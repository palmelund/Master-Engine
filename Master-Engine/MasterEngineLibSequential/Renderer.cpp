#include "stdafx.h"
#include "Renderer.h"
#include "SFML/Graphics.hpp"

std::unordered_set<const sf::Sprite*> Renderer::sprites_{};
sf::RenderWindow Renderer::window_{};
sf::Vector2i* Renderer::window_size{};
sf::Font Renderer::font_{};
std::vector<sf::Text> Renderer::text_vector_{};

void Renderer::init(std::string window_name, int width, int height)
{
	const auto& v2 = sf::Vector2u(width, height);
	window_.setSize(v2);  // = sf::RenderWindow{ sf::VideoMode(width, height), window_name };
	window_.setTitle(window_name);
	Renderer::window_size = new sf::Vector2i(width, height);
	window_.create(sf::VideoMode(width, height), window_name);

	if(!font_.loadFromFile("Roboto-Regular.ttf"))
	{
		throw std::exception("Failed to load font!");
	}
}

void Renderer::render()
{
	window_.clear(sf::Color::Black);
	for (auto& sprite : sprites_)
	{
		window_.draw(*sprite);
	}

	for (auto& text : text_vector_)
	{
		window_.draw(text);
	}
	text_vector_.clear();

	window_.display();
}

void Renderer::add_sprite(const sf::Sprite* sprite)
{
	sprites_.insert(sprite);
}

void Renderer::remove_sprite(const sf::Sprite& sprite)
{
	const auto ptr = &sprite;
	sprites_.erase(ptr);
}

bool Renderer::is_open()
{
	return window_.isOpen();
}

bool Renderer::poll_event(sf::Event& event)
{
	return window_.pollEvent(event);
}

void Renderer::close()
{
	window_.close();
}

sf::Vector2i* Renderer::get_window_size()
{
	return Renderer::window_size;
}

void Renderer::draw_text(const std::string& txt, int x_pos, int y_pos, int size)
{
	sf::Text text;
	text.setFont(font_);
	text.setString(txt);
	text.setCharacterSize(size);
	text.setFillColor(sf::Color::Magenta);

	text.setPosition(x_pos, y_pos);

	text_vector_.emplace_back(text);
}

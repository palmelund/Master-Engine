#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <unordered_set>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Renderer
{
public:
	Renderer() = delete;
	Renderer(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer& operator=(Renderer&&) = delete;
	~Renderer() = delete;

	static void init(std::string window_name, int width, int height);

	static void render();

	static void add_sprite(const sf::Sprite& sprite);

	static void remove_sprite(const sf::Sprite& sprite);

	static bool is_open();
	static bool poll_event(sf::Event& event);
	static void close();
private:
	static std::unordered_set<const sf::Sprite*> sprites_;
	static sf::RenderWindow window_;
};

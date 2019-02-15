#pragma once

#include "SFML/Graphics.hpp"

#include <string>
#include <array>

enum class key_status
{
	unpressed,
	pressed,
	hold,
	lifted,
};

enum class key_code
{
	key_w,
	key_a,
	key_s,
	key_d,

	Count
};

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	GameEngine(GameEngine&& engine) noexcept = default;
	GameEngine& operator=(GameEngine&& engine) noexcept = default;

	GameEngine(const GameEngine&) = delete;
	GameEngine& operator=(const GameEngine&) = delete;

	void init(const std::string& window_name, int window_width, int window_height);
	void update();

	key_status get_key(key_code key);

private:
	sf::RenderWindow* window_;
	std::array<key_status, (size_t)key_code::Count> key_statuses_;

	void process_input();
	inline void process_key_input(sf::Keyboard::Key gl_key, key_code key);

	std::vector<sf::Sprite*> sprites_;
	std::vector<sf::Texture*> textures_;

	void render();

	float delta_time_;
	unsigned long long program_start_time_;
	unsigned long long program_current_time_;
};


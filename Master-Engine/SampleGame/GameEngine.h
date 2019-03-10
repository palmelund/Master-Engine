#pragma once

#include "SFML/Graphics.hpp"

#include <array>

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	void init();

	GameEngine(GameEngine&& engine) noexcept = default;
	GameEngine& operator=(GameEngine&& engine) noexcept = default;

	GameEngine(const GameEngine&) = delete;
	GameEngine& operator=(const GameEngine&) = delete;

	void run();

private:
	std::vector<float> delta_list;

};

#pragma once

#include "SFML/Graphics.hpp"

#include <string>
#include <array>
#include <unordered_set>
#include "KeyStatus.h"
#include "KeyCode.h"

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

	float delta_time_;
	unsigned long long program_start_time_;
	unsigned long long program_current_time_;
};

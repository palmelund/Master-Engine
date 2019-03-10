#pragma once
#include "KeyStatus.h"
#include "KeyCode.h"
#include <SFML/Window/Keyboard.hpp>
#include <array>

class Input
{
public:
	Input() = delete;

	Input(const Input&) = delete;
	Input(Input&&) = delete;
	Input& operator=(const Input&) = delete;
	Input& operator=(Input&&) = delete;

	~Input() = delete;

	static KeyStatus get_input_state(KeyCode key_code);
	static bool get_key_pressed(KeyCode key_code);
	static bool get_key_hold(KeyCode key_code);
	static bool get_key_lift(KeyCode key_code);

	static void process_input();
	static void process_key_input(sf::Keyboard::Key gl_key, KeyCode key);

private:
	static std::array<KeyStatus, static_cast<size_t>(KeyCode::Count)> key_statuses_;
};


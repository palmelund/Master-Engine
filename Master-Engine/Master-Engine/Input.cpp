#include "pch.h"
#include "Input.h"

std::array<KeyStatus, static_cast<size_t>(KeyCode::Count)> Input::key_statuses_;

void Input::process_key_input(sf::Keyboard::Key gl_key, KeyCode key)
{
	if (sf::Keyboard::isKeyPressed(gl_key))
	{
		if (key_statuses_[static_cast<unsigned long long>(key)] == KeyStatus::unpressed || key_statuses_[static_cast<unsigned long long>(key)] == KeyStatus::lifted)
		{
			key_statuses_[static_cast<unsigned long long>(key)] = KeyStatus::pressed;
		}
		else
		{
			key_statuses_[static_cast<unsigned long long>(key)] = KeyStatus::hold;
		}
	}
	else if (!sf::Keyboard::isKeyPressed(gl_key) && (key_statuses_[static_cast<unsigned long long>(key)] == KeyStatus::pressed || key_statuses_[static_cast<unsigned long long>(key)] == KeyStatus::hold))
	{
		key_statuses_[static_cast<unsigned long long>(key)] = KeyStatus::lifted;
	}
	else
	{
		key_statuses_[static_cast<unsigned long long>(key)] = KeyStatus::unpressed;
	}
}

KeyStatus Input::get_input_state(KeyCode key_code)
{
	return key_statuses_[static_cast<long long int>(key_code)];
}

bool Input::get_key_pressed(KeyCode key_code)
{
	return get_input_state(key_code) == KeyStatus::pressed;
}

bool Input::get_key_hold(KeyCode key_code)
{
	return get_input_state(key_code) == KeyStatus::pressed || get_input_state(key_code) == KeyStatus::hold;
}

bool Input::get_key_lift(KeyCode key_code)
{
	return get_input_state(key_code) == KeyStatus::lifted;
}


void Input::process_input()
{
	process_key_input(sf::Keyboard::W, KeyCode::key_w);
	process_key_input(sf::Keyboard::A, KeyCode::key_a);
	process_key_input(sf::Keyboard::S, KeyCode::key_s);
	process_key_input(sf::Keyboard::D, KeyCode::key_d);
}

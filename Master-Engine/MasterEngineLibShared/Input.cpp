#include "stdafx.h"
#include "Input.h"

namespace MasterEngine {
	namespace LibShared {

		std::array<KeyStatus, static_cast<size_t>(sf::Keyboard::KeyCount)> Input::key_statuses_;
		std::vector<sf::Keyboard::Key> Input::enabled_keys_{};

		void Input::process_key_input(sf::Keyboard::Key key)
		{
			if (sf::Keyboard::isKeyPressed(key))
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
			else if (!sf::Keyboard::isKeyPressed(key) && (key_statuses_[static_cast<unsigned long long>(key)] == KeyStatus::pressed || key_statuses_[static_cast<unsigned long long>(key)] == KeyStatus::hold))
			{
				key_statuses_[static_cast<unsigned long long>(key)] = KeyStatus::lifted;
			}
			else
			{
				key_statuses_[static_cast<unsigned long long>(key)] = KeyStatus::unpressed;
			}
		}

		void Input::init(const std::vector<sf::Keyboard::Key>& enabled_keys)
		{
			enabled_keys_ = enabled_keys;
		}

		void Input::init(std::vector<sf::Keyboard::Key>&& enabled_keys)
		{
			enabled_keys_ = std::move(enabled_keys);
		}

		KeyStatus Input::get_input_state(sf::Keyboard::Key key_code)
		{
			return key_statuses_[static_cast<long long int>(key_code)];
		}

		bool Input::get_key_pressed(sf::Keyboard::Key key_code)
		{
			return get_input_state(key_code) == KeyStatus::pressed;
		}

		bool Input::get_key_hold(sf::Keyboard::Key key_code)
		{
			return get_input_state(key_code) == KeyStatus::pressed || get_input_state(key_code) == KeyStatus::hold;
		}

		bool Input::get_key_lift(sf::Keyboard::Key key_code)
		{
			return get_input_state(key_code) == KeyStatus::lifted;
		}


		void Input::process_input()
		{
			for (auto key : enabled_keys_)
			{
				process_key_input(key);
			}

			//process_key_input(sf::Keyboard::W);
			//process_key_input(sf::Keyboard::A);
			//process_key_input(sf::Keyboard::S);
			//process_key_input(sf::Keyboard::D);
		}

	}
}
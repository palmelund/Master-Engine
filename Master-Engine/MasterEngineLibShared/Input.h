#pragma once
#include "KeyStatus.h"
#include <SFML/Window/Keyboard.hpp>
#include <array>
#include <vector>

namespace MasterEngine {
	namespace LibShared {

		class Input
		{
		public:
			Input() = delete;

			Input(const Input&) = delete;
			Input(Input&&) = delete;
			Input& operator=(const Input&) = delete;
			Input& operator=(Input&&) = delete;

			~Input() = delete;

			static void init(const std::vector<sf::Keyboard::Key>& enabled_keys);
			static void init(std::vector<sf::Keyboard::Key>&& enabled_keys);

			static KeyStatus get_input_state(sf::Keyboard::Key key);
			static bool get_key_pressed(sf::Keyboard::Key key);
			static bool get_key_hold(sf::Keyboard::Key key);
			static bool get_key_lift(sf::Keyboard::Key key);

			static void process_input();
			static void process_key_input(sf::Keyboard::Key key);

		private:
			static std::vector<sf::Keyboard::Key> enabled_keys_;
			static std::array<KeyStatus, static_cast<size_t>(sf::Keyboard::KeyCount)> key_statuses_;
		};

	}
}
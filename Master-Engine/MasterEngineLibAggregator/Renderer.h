#pragma once
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "GameObject.h"
#include "BatchDrawable.h"
#include "VectorWrapper.h"

namespace MasterEngine {
	namespace LibAggregator {

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

			static void add_drawable_object(GameObject* drawable_object);
			static void remove_drawable_object(GameObject* drawable_object);

			static void draw_text(const std::string& txt, int x_pos, int y_pos, int size);

			static bool is_open();
			static bool poll_event(sf::Event& event);
			static void close();

			static sf::Vector2i* get_window_size();

			static void set_sprite_sheet(const sf::Texture& sprite_sheet, int sprite_width, int sprite_height);

			static sf::Vector2f get_sprite_size();


		private:
			static BatchDrawable batch_drawable_;
			static sf::RenderWindow window_;
			static sf::Vector2i* window_size;

			static sf::Font font_;
			static VectorWrapper<sf::Text> text_vector_;

			static std::mutex modify_batch_mutex_;
		};
	}
}

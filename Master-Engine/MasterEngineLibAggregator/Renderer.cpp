#include "stdafx.h"
#include "Renderer.h"
#include "SFML/Graphics.hpp"
#include "VectorWrapper.h"

namespace MasterEngine {
	namespace LibAggregator {

		BatchDrawable Renderer::batch_drawable_{};
		sf::RenderWindow Renderer::window_{};
		sf::Vector2i* Renderer::window_size_{};
		sf::Font Renderer::font_{};
		VectorWrapper<sf::Text*> Renderer::text_vector_{};
		std::mutex Renderer::modify_batch_mutex_{};

		void Renderer::init(const std::string& window_name, const int width, const int height)
		{
			const auto& v2 = sf::Vector2u(width, height);
			window_.setSize(v2);
			window_.setTitle(window_name);
			Renderer::window_size_ = new sf::Vector2i(width, height);
			window_.create(sf::VideoMode(width, height), window_name);

			if (!font_.loadFromFile("Roboto-Regular.ttf"))
			{
				throw std::exception("Failed to load font!");
			}
		}

		void Renderer::render()
		{
			window_.clear(sf::Color::Cyan);
			batch_drawable_.update();
			window_.draw(batch_drawable_);

			for (auto text : text_vector_.get_value())
			{
				window_.draw(*text);
				text_vector_ -= text;
				delete text;
			}
			text_vector_.clear();

			window_.display();
		}

		void Renderer::add_drawable_object(GameObject* drawable_object)
		{
			std::unique_lock<std::mutex> lock(modify_batch_mutex_);
			batch_drawable_.add(drawable_object);
		}

		void Renderer::remove_drawable_object(GameObject* drawable_object)
		{
			std::unique_lock<std::mutex> lock(modify_batch_mutex_);
			batch_drawable_.remove(drawable_object);
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
			return Renderer::window_size_;
		}

		void Renderer::set_sprite_sheet(const sf::Texture& sprite_sheet, const int sprite_width, const int sprite_height)
		{
			batch_drawable_.set_texture(sprite_sheet, sprite_sheet.getSize().x, sprite_sheet.getSize().y, sprite_width, sprite_height);
		}

		sf::Vector2f Renderer::get_sprite_size()
		{
			return sf::Vector2f{ static_cast<float>(batch_drawable_.get_sprite_width()), static_cast<float>(batch_drawable_.get_sprite_height()) };
		}

		void Renderer::draw_text(const std::string& txt, const int x_pos, const int y_pos, const int size)
		{
			auto* text = new sf::Text{};
			text->setFont(font_);
			text->setString(txt);
			text->setCharacterSize(size);
			text->setFillColor(sf::Color::Magenta);

			text->setPosition(static_cast<float>(x_pos), static_cast<float>(y_pos));

			text_vector_ += text;
		}
	}
}
#include "stdafx.h"
#include "BatchDrawable.h"

namespace MasterEngine {
	namespace LibAggregator {

		BatchDrawable::BatchDrawable() : style_sheet_width_(0), style_sheet_height_(0)
		{
			vertices_.setPrimitiveType(sf::Quads);
		}

		BatchDrawable::~BatchDrawable() = default;

		void BatchDrawable::set_texture(const sf::Texture& texture, int style_sheet_width, int style_sheet_height, int sprite_width, int sprite_height)
		{
			texture_ = texture;

			style_sheet_width_ = style_sheet_width;
			style_sheet_height_ = style_sheet_height;

			sprite_width_ = sprite_width;
			sprite_height_ = sprite_height;

		}

		void BatchDrawable::add(GameObject* game_object)
		{
			drawable_objects_ += (game_object);
		}

		void BatchDrawable::remove(GameObject* game_object)
		{
			const auto it = std::find(drawable_objects_.get_value().begin(), drawable_objects_.get_value().end(), game_object);

			if (it != drawable_objects_.get_value().end())
			{
				drawable_objects_ -= game_object;
			}
		}


		void BatchDrawable::update()
		{
			const auto size = static_cast<int>(drawable_objects_.size());
			vertices_.resize(static_cast<size_t>(size) * 4);

			for (auto i = 0; i < size; i++)
			{
				auto* quad = &vertices_[static_cast<size_t>(i) * 4];
				const auto& game_object = drawable_objects_[i];

				const auto pos = game_object->get_position();

				quad[0].position = sf::Vector2f(pos.x, pos.y);
				quad[1].position = sf::Vector2f(pos.x + game_object->get_scaled_size().x, pos.y);
				quad[2].position = sf::Vector2f(pos.x + game_object->get_scaled_size().x, pos.y + game_object->get_scaled_size().y);
				quad[3].position = sf::Vector2f(pos.x, pos.y + game_object->get_scaled_size().y);

				quad[0].texCoords = sf::Vector2f(static_cast<float>(game_object->sprite_pos() * sprite_width_), 0.0f);
				quad[1].texCoords = sf::Vector2f(static_cast<float>(game_object->sprite_pos() * sprite_width_ + sprite_width_), 0.0f);
				quad[2].texCoords = sf::Vector2f(static_cast<float>(game_object->sprite_pos() * sprite_width_ + sprite_width_), static_cast<float>(sprite_height_));
				quad[3].texCoords = sf::Vector2f(static_cast<float>(game_object->sprite_pos() * sprite_width_), static_cast<float>(sprite_height_));
			}
		}

		int BatchDrawable::get_style_sheet_width() const
		{
			return style_sheet_width_;
		}

		int BatchDrawable::get_style_sheet_height() const
		{
			return style_sheet_height_;
		}

		int BatchDrawable::get_sprite_width() const
		{
			return sprite_width_;
		}

		int BatchDrawable::get_sprite_height() const
		{
			return sprite_height_;
		}

		void BatchDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const
		{
			states.transform *= getTransform();
			states.texture = &texture_;
			target.draw(vertices_, states);
		}

	}
}
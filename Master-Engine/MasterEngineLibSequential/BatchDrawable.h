#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <vector>
#include "GameObject.h"
#include <unordered_set>
#include <set>

class BatchDrawable : public sf::Drawable, public sf::Transformable
{
public:
	explicit BatchDrawable();
	~BatchDrawable();

	void set_texture(const sf::Texture& texture, int style_sheet_width, int style_sheet_height, int sprite_width, int sprite_height);

	void add(GameObject* game_object);
	void remove(GameObject* game_object);

	void update();

	int get_style_sheet_width() const;
	int get_style_sheet_height() const;
	int get_sprite_width() const;
	int get_sprite_height() const;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::vector<GameObject*> drawable_objects_;

	sf::VertexArray vertices_;
	sf::Texture texture_;

	int style_sheet_width_;
	int style_sheet_height_;

	int sprite_width_{};
	int sprite_height_{};
};


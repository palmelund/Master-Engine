#pragma once
#include "GameEngine.h"

class GameObject
{
public:
	explicit GameObject(bool requires_input);

	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;

	GameObject(GameObject&&) = default;
	GameObject& operator=(GameObject&&) = default;

	inline bool requires_input() const noexcept;
	inline unsigned long long get_id() const noexcept;

	void set_sprite(sf::Texture& texture);
	void unset_sprite();

protected:
	~GameObject();

private:
	bool requires_input_;
	unsigned long long id_;

	sf::Sprite sprite_;
	bool draw_;
};


#pragma once
#include "GameEngine.h"
#include "SFML/Graphics.hpp"
#include "Tags.h"
#include "Collider.h"
#include "Collider.h"

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

	void start_up();
	void update();
	void OnCollision(GameObject* collider);

	void set_sprite(sf::Texture& texture);
	void unset_sprite();

	void add_collider(Collider& collider);

	template<typename CONTAINER>
	void add_colliders(const CONTAINER& collider);
	
	std::vector<Collider*>& get_colliders();


	void set_position(sf::Vector2f);
	sf::Vector2f get_position();

	Tags get_tag();

	float get_scale();
	void set_scale(float);



protected:
	~GameObject();

private:
	bool requires_input_;
	unsigned long long id_;


	std::vector<Collider*> colliders_;
	Tags tag_;
	sf::Vector2f position_;
	sf::Sprite sprite_;
	bool draw_;

	float scale_;
};

template <typename CONTAINER>
void GameObject::add_colliders(const CONTAINER& collider)
{
}


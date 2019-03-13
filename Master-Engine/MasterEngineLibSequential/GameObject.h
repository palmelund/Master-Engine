#pragma once
#include "SFML/Graphics.hpp"
#include "Collider.h"
#include "Transform.h"

enum class Tags;
class Collider;//Needed to break cirkuler pointer.

class GameObject
{
public:
	explicit GameObject(bool requires_input, bool collision_code = false);
	~GameObject();

	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;

	GameObject(GameObject&&) = default;
	GameObject& operator=(GameObject&&) = default;

	inline bool requires_input() const noexcept;
	unsigned long long get_id() const noexcept;

	virtual void start_up();
	virtual void update();
	virtual void OnCollision(GameObject* collider);
	void collision_check();

	void set_sprite(sf::Texture& texture);
	void unset_sprite();

	void add_collider(Collider* collider);

	template<typename CONTAINER>
	void add_colliders(const CONTAINER& collider);
	
	std::vector<Collider*>& get_colliders();


	void set_position(sf::Vector2f);
	sf::Vector2f get_position();

	void set_tag(Tags);
	Tags get_tag();

	float get_width_scale();
	float get_height_scale();
	float get_width_size();
	float get_height_size();
	void set_scale(float, float);
	void set_size(float, float);
	void add_velocity(sf::Vector2f);
	void set_velocity(sf::Vector2f);

	sf::Vector2f get_velocity();
protected:
	sf::Sprite sprite_;

private:
	sf::Vector2f velocity_;
	bool requires_input_;
	bool collision_code_;
	unsigned long long id_;


	std::vector<Collider*> colliders_;
	bool ColliderOverLap(Transform object1, Transform Object2);
	Tags tag_;
	sf::Vector2f position_;	
	
	bool draw_;

	float height_scale_;
	float width_scale_;
};

template <typename CONTAINER>
void GameObject::add_colliders(const CONTAINER& collider)
{
}
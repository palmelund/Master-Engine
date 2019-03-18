#include "pch.h"
#include "GravityWell.h"
#include "../MasterEngineLibSequential/ResourceManager.h"
#include "../MasterEngineLibShared/Time.h"
#include "SpriteIndexes.h"

#define SIZE 160.0f
#define pullforce 1.0f

GravityWell::GravityWell() : GameObject(true)
{
	GameObject::set_sprite(GRAVITY_WELL_SPRITE);
	GameObject::set_size(SIZE, SIZE);
	GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });
}


GravityWell::~GravityWell()
{
}

void GravityWell::OnCollision(GameObject * collider)
{
	float side_a = (get_position().x + (SIZE / 2.0f)) - (collider->get_position().x + (collider->get_width_size() / 2.0f));
	float side_b = (get_position().y + (SIZE / 2.0f)) - (collider->get_position().y + (collider->get_height_size() / 2.0f));
	float side_c = std::sqrt(std::pow(side_a, 2) + std::pow(side_b, 2));
	float cal_pullforce = (SIZE- side_c) * pullforce;
	sf::Vector2f direction_vector{ side_a / side_c , side_b / side_c };

	collider->add_velocity(sf::Vector2f{ direction_vector.x*cal_pullforce*Time::DeltaTime() ,direction_vector.x*cal_pullforce*Time::DeltaTime() });
}

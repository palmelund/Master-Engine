#include "pch.h"
#include "GravityWell.h"
#include "../MasterEngineLibSequential/ResourceManager.h"
#include "M_Transform.h"

#define SIZE 80.0f
#define pullforce 2.0f

GravityWell::GravityWell() : GameObject(false, true)
{
	GameObject::set_sprite(ResourceManager::get_texture("gravitywell.png"));
	GameObject::set_size(SIZE, SIZE);
	GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, sf::Vector2f{sprite_.getLocalBounds().width, sprite_.getLocalBounds().height} });
}


GravityWell::~GravityWell()
{
}

void GravityWell::OnCollision(GameObject * collider)
{
	M_Transform* transform = dynamic_cast<M_Transform*>(collider);
	if(transform)
	{
		float side_a = get_position().x - collider->get_position().x;
		float side_b = get_position().y - collider->get_position().y;
		float side_c = std::sqrt(std::pow(side_a, 2) + std::pow(side_b, 2));
		float cal_pullforce = SIZE - side_c * pullforce;
		sf::Vector2f direction_vector{ side_a / side_c , side_b / side_c };

		transform->add_velocity(sf::Vector2f{ direction_vector.x*cal_pullforce,direction_vector.x*cal_pullforce });

	}

	

	
	

}

#include "pch.h"
#include "GravityWell.h"
#include "../MasterEngineLibSequential/ResourceManager.h"
#include "../MasterEngineLibShared/Time.h"
#include "../CaptainEverythingShared/SpriteIndexes.h"
#include "../CaptainEverythingShared/Constants.h"

namespace CaptainEverythingSequential {
	using namespace CaptainEverythingShared;
	using namespace MasterEngine::LibShared;

	GravityWell::GravityWell() : GameObject(true)
	{
		GameObject::set_sprite(SpriteIndexes::gravity_well_sprite);
		GameObject::set_size(Constants::gravity_well_size, Constants::gravity_well_size);
		GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });
	}


	GravityWell::~GravityWell()
	{
	}

	void GravityWell::on_collision(GameObject* collider)
	{
		float side_a = (get_position().x + (Constants::gravity_well_size / 2.0f)) - (collider->get_position().x + (collider->get_width_size() / 2.0f));
		float side_b = (get_position().y + (Constants::gravity_well_size / 2.0f)) - (collider->get_position().y + (collider->get_height_size() / 2.0f));
		float side_c = std::sqrt(std::pow(side_a, 2) + std::pow(side_b, 2));
		float cal_pullforce = (Constants::gravity_well_size - side_c) * Constants::gravity_well_pull_force;
		sf::Vector2f direction_vector{ side_a / side_c , side_b / side_c };

		collider->add_velocity(sf::Vector2f{ direction_vector.x * cal_pullforce * Time::delta_time() ,direction_vector.x * cal_pullforce * Time::delta_time() });
	}
}

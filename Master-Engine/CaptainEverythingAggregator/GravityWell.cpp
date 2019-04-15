#include "pch.h"
#include "GravityWell.h"
#include "../MasterEngineLibAggregator/ResourceManager.h"
#include "../MasterEngineLibShared/Time.h"
#include "Player.h"
#include "../CaptainEverythingShared/SpriteIndexes.h"
#include "../CaptainEverythingShared/Constants.h"

namespace CaptainEverythingAggregator {
	using namespace CaptainEverythingShared;

	GravityWell::GravityWell(sf::Vector2f position) : GameObject(true)
	{
		GameObject::set_sprite(GRAVITY_WELL_SPRITE);
		GameObject::set_size(GRAVITY_WELL_SIZE, GRAVITY_WELL_SIZE);
		GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });
		GameObject::position_.set_vector(position);
	}


	GravityWell::~GravityWell()
	{
	}

	void GravityWell::on_collision(GameObject* collider)
	{
		float side_a = (get_position().x + (GRAVITY_WELL_SIZE / 2.0f)) - (collider->get_position().x + (collider->get_width_size() / 2.0f));
		float side_b = (get_position().y + (GRAVITY_WELL_SIZE / 2.0f)) - (collider->get_position().y + (collider->get_height_size() / 2.0f));
		float side_c = std::sqrt(std::pow(side_a, 2) + std::pow(side_b, 2));
		float cal_pullforce = (GRAVITY_WELL_SIZE - side_c) * GRAVITY_WELL_PULL_FORCE;
		sf::Vector2f direction_vector{ side_a / side_c , side_b / side_c };

		collider->add_velocity(sf::Vector2f{ direction_vector.x * cal_pullforce * Time::delta_time() ,direction_vector.x * cal_pullforce * Time::delta_time() });
	}
}

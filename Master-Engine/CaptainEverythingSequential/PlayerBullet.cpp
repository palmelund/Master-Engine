#include "pch.h"
#include "PlayerBullet.h"
#include "../MasterEngineLibSequential/GameEngine.h"
#include "../MasterEngineLibShared/Time.h"
#include "../MasterEngineLibShared/Tags.h"
#include "../MasterEngineLibSequential/Renderer.h"
#include "Spawner.h"
#include "../CaptainEverythingShared/SpriteIndexes.h"
#include "../CaptainEverythingShared/Constants.h"

namespace CaptainEverythingSequential {
	using namespace CaptainEverythingShared;
	using namespace MasterEngine::LibShared;

	PlayerBullet::PlayerBullet() : GameObject(true)
	{
		size_ = Constants::player_bullet_size;
		set_velocity(sf::Vector2f{ 300.0f, 0.0f });
		GameObject::set_sprite(SpriteIndexes::bullet_sprite);
		GameObject::set_size(static_cast<float>(size_), static_cast<float>(size_));
		GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, get_scaled_size() });
		GameObject::set_tag(Tags::Bullet);
	}


	PlayerBullet::~PlayerBullet()
	{

	}

	void PlayerBullet::update()
	{
		sf::Vector2f velocity = GameObject::get_velocity();
		GameObject::set_position(sf::Vector2f{ GameObject::get_position().x + (velocity.x * Time::delta_time()), GameObject::get_position().y + (velocity.y * Time::delta_time()) });
		if (GameObject::get_position().x > Renderer::get_window_size()->x)
		{
			GameEngine::remove_game_object(this);
		}
	}

	void PlayerBullet::on_collision(GameObject* collider)
	{
		switch (collider->get_tag())
		{
		case Tags::Enemy:
			Spawner::get_single_ton()->add_enemy_hit();
		case  Tags::EnemyBullet:
			GameEngine::remove_game_object(collider);
			GameEngine::remove_game_object(this);
			break;
		default:
			break;
		}
	}
}

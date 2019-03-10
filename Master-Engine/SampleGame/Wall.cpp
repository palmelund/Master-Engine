#include "pch.h"
#include "Wall.h"
#include "../MasterEngineLibSequential/ResourceManager.h"
#include "../MasterEngineLibShared/Tags.h"

Wall::Wall(const std::string& texture, sf::Vector2f position, float size) : GameObject(false)
{
	GameObject::set_sprite(ResourceManager::get_texture(texture));
	GameObject::set_size(size, size);
	GameObject::add_collider(new Collider{ sf::Vector2f{0,0}, sf::Vector2f{sprite_.getLocalBounds().width, sprite_.getLocalBounds().height} });
	GameObject::set_position(position);
	GameObject::set_tag(Tags::Enemy);
}

Wall::~Wall()
{
}

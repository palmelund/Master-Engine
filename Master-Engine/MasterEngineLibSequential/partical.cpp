#include "stdafx.h"
#include "partical.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameEngine.h"


partical::partical(const std::string& texture, sf::Vector2f velocity, sf::Vector2f position) : GameObject(false)
{
	size_ = 10;
	velocity_ = velocity;
	GameObject::set_sprite(ResourceManager::get_texture(texture));
	GameObject::set_size(size_, size_);
	GameObject::set_position(position);
}


partical::~partical()
{
}

void partical::update()
{
	if(GameObject::get_position().y > Renderer::get_window_size()->y)
	{
		GameEngine::remove_game_object(this);
	}
	
	velocity_ = sf::Vector2f{ 0.5f * 1.2041f * (velocity_.x * velocity_.x) * 0.004f * (4.0f * 4.0f), 0.5f * 1.2041f * (velocity_.y * velocity_.y) * 0.004f * (4.0f * 4.0f) };
	velocity_.y += 3.0f; //Gravity
	GameObject::set_position(sf::Vector2f{GameObject::get_position().x+velocity_.x, GameObject::get_position().y+velocity_.y});
}

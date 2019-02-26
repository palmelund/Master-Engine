#include "pch.h"
#include "ResourceManager.h"
#include <SFML/Graphics/Texture.hpp>

std::unordered_map<std::string, sf::Texture> ResourceManager::textures_{};

sf::Texture& ResourceManager::get_texture(const std::string& sprite_name)
{
	auto finding = textures_.find(sprite_name);
	if(finding == textures_.end())
	{
		return load_texture(sprite_name);
	} else 	{
		return finding->second;
	}
}

sf::Texture& ResourceManager::load_texture(const std::string& sprite_name)
{
	auto pair = textures_.try_emplace(sprite_name, sf::Texture{});
	auto& texture = pair.first->second;

	texture.loadFromFile(sprite_name);

	return texture;
}

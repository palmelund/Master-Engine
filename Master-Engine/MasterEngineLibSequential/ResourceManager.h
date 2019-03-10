#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <map>
#include <unordered_map>

class ResourceManager
{
public:
	ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	~ResourceManager() = delete;

	static sf::Texture& get_texture(const std::string&);
private:
	static std::unordered_map<std::string, sf::Texture> textures_;
	static sf::Texture& load_texture(const std::string&);
};


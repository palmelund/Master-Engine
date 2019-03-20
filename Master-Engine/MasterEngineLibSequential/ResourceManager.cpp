#include "stdafx.h"
#include "ResourceManager.h"
#include <SFML/Graphics/Texture.hpp>

namespace MasterEngine {
	namespace LibSequential {
		std::unordered_map<std::string, sf::Texture> ResourceManager::textures_{};

		sf::Texture& ResourceManager::load_texture(const std::string& texture_name)
		{
			auto finding = textures_.find(texture_name);
			if (finding != textures_.end())
			{
				return finding->second;
			}

			auto pair = textures_.try_emplace(texture_name, sf::Texture{});
			auto& texture = pair.first->second;

			if (!texture.loadFromFile(texture_name))
			{
				throw std::exception();
			}

			return texture;
		}

	}
}
#pragma once
#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>

namespace MasterEngine
{
	namespace LibParallel {

		class ResourceManager
		{
		public:
			ResourceManager() = delete;
			ResourceManager(const ResourceManager&) = delete;
			ResourceManager(ResourceManager&&) = delete;
			ResourceManager& operator=(const ResourceManager&) = delete;
			ResourceManager& operator=(ResourceManager&&) = delete;
			~ResourceManager() = delete;

			static sf::Texture& load_texture(const std::string& texture_name);

		private:
			static std::unordered_map<std::string, sf::Texture> textures_;
		};

	}
}
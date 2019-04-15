#pragma once
#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>

namespace MasterEngine
{
	namespace LibAggregator {

		class ResourceManager
		{
		public:
			ResourceManager() = delete;

			static sf::Texture& load_texture(const std::string& texture_name);

		private:
			static std::unordered_map<std::string, sf::Texture> textures_;
		};

	}
}
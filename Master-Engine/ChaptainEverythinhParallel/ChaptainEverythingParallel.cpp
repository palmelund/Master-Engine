// ChaptainEverythinhParallel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Spawner.h"
#include "../MasterEngineLibParallel/GameEngine.h"
#include "../MasterEngineLibParallel/ResourceManager.h"
#include "../MasterEngineLibParallel/Renderer.h"
#include "../CaptainEverythingShared/Constants.h"
#include "../CaptainEverythingShared/SpriteIndexes.h"
#include <iostream>

using namespace MasterEngine::LibParallel;
using namespace CaptainEverythingParallel;
using namespace CaptainEverythingShared;

int main(int argc, char* argv[])
{
	if (argc != 1 && argc != 5)
	{
		std::cout << "Expected either none or 2 arguments" << std::endl;
	}

	if (argc == 5)
	{
		Constants::set_changeable_constants(argv[1], argv[2], argv[3]);
		MasterEngine::LibParallel::Renderer::init(argv[4], Constants::screen_width, Constants::screen_height);
	}
	else {
		MasterEngine::LibParallel::Renderer::init("Master Engine", Constants::screen_width, Constants::screen_height);
	}
	Renderer::set_sprite_sheet(ResourceManager::load_texture("spritesheet.png"), SpriteIndexes::sprite_width, SpriteIndexes::sprite_height);

	GameEngine::init();
	GameEngine::instantiate(new Spawner(), sf::Vector2f{ 0,0 });

	GameEngine::run();

	return  EXIT_SUCCESS;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

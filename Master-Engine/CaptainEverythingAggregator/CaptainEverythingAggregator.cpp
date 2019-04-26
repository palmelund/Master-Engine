// CaptainEverythingAggregator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "../MasterEngineLibAggregator/GameEngine.h"
#include "../CaptainEverythingShared/SpriteIndexes.h"
#include "../MasterEngineLibAggregator/Renderer.h"
#include "../CaptainEverythingShared/Constants.h"
#include "../MasterEngineLibAggregator/ResourceManager.h"
#include <iostream>

int main()
{
	using namespace CaptainEverythingShared;

	MasterEngine::LibAggregator::Renderer::init("Master Engine", Constants::screen_width, Constants::screen_height);
	MasterEngine::LibAggregator::Renderer::set_sprite_sheet(MasterEngine::LibAggregator::ResourceManager::load_texture("spritesheet.png"), SpriteIndexes::sprite_width, SpriteIndexes::sprite_height);

	MasterEngine::LibAggregator::GameEngine::init();

	MasterEngine::LibAggregator::GameEngine::run();

	std::string str;
	std::getline(std::cin, str);

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

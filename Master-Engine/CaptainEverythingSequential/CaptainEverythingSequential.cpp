// CaptainEverythingSequential.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "../MasterEngineLibSequential/GameEngine.h"
#include "../MasterEngineLibSequential/Renderer.h"
#include "Spawner.h"

int main()
{
#ifdef DETECT_MEMORY_LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Renderer::init("Master Engine", 800, 500);
	GameEngine::init();

	GameEngine::Instantiate(new Spawner(), sf::Vector2f{ 0,0 });

	GameEngine::run();
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

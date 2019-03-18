// SampleGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "../MasterEngineLibShared/ThreadPool.h"
#include "../MasterEngineLibSequential/Renderer.h"
#include "../MasterEngineLibSequential/GameEngine.h"
#include "Wall.h"
#include "Player.h"
#include "../MasterEngineLibShared/Input.h"

int main()
{
#ifdef DETECT_MEMORY_LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	ThreadPool::CreateThreadPool();
	
	const std::vector<sf::Keyboard::Key> keys = {sf::Keyboard::W, sf::Keyboard::A ,sf::Keyboard::S ,sf::Keyboard::D };
	
	Input::init(keys);
	Renderer::init("Master Engine", 800, 600);
	new Player{ "awesomeface.png" };

	for (int i = 0; i < 10; i++)
	{
		new Wall{ "wall.png" , sf::Vector2f{300.0f, 0.0f + (30.0f * i)}, 30.0f };
	}

	for (int i = 0; i < 11; i++)
	{
		new Wall{ "wall.png" , sf::Vector2f{300.0f - (30.0f*i), 330.0f}, 30.0f };
	}
		
	GameEngine::init();



	GameEngine::run();

	ThreadPool::ClearThreadPool();
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

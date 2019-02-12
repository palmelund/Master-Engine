#include "pch.h"
#include "GameEngine.h"

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
	glfwTerminate();
}

void GameEngine::init(const std::string& window_name, int window_width, int window_height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window_ = glfwCreateWindow(window_width, window_height, window_name.c_str(), NULL, NULL);
	if (window_ == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(1);
	}

	glViewport(0, 0, window_width, window_height);
}

void GameEngine::update()
{
	while (!glfwWindowShouldClose(window_))
	{
		glfwSwapBuffers(window_);
		glfwPollEvents();

		process_input();

		if (get_key(key_code::key_a) == key_status::pressed)
		{
			std::cout << "A pressed." << std::endl;
		}

		if (get_key(key_code::key_d) == key_status::hold)
		{
			std::cout << "D hold." << std::endl;
		}

		if(get_key(key_code::key_w) == key_status::lifted)
		{
			std::cout << "W lifted." << std::endl;
		}
	}
}

key_status GameEngine::get_key(key_code key)
{
	return key_statuses_[static_cast<long long int>(key)];
}

void GameEngine::process_input()
{
	process_key_input(GLFW_KEY_W, key_code::key_w);
	process_key_input(GLFW_KEY_A, key_code::key_a);
	process_key_input(GLFW_KEY_S, key_code::key_s);
	process_key_input(GLFW_KEY_D, key_code::key_d);
}

void GameEngine::process_key_input(uint8_t gl_key, key_code key)
{
	if (glfwGetKey(window_, gl_key) == GLFW_PRESS)
	{
		if (key_statuses_[static_cast<unsigned long long>(key)] == key_status::unpressed || key_statuses_[static_cast<unsigned long long>(key)] == key_status::lifted)
		{
			key_statuses_[static_cast<unsigned long long>(key)] = key_status::pressed;
		}
		else
		{
			key_statuses_[static_cast<unsigned long long>(key)] = key_status::hold;
		}
	}
	else if (glfwGetKey(window_, gl_key) == GLFW_RELEASE && (key_statuses_[static_cast<unsigned long long>(key)] == key_status::pressed || key_statuses_[static_cast<unsigned long long>(key)] == key_status::hold))
	{
		key_statuses_[static_cast<unsigned long long>(key)] = key_status::lifted;
	}
	else
	{
		key_statuses_[static_cast<unsigned long long>(key)] = key_status::unpressed;
	}
}

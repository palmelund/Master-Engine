#include "pch.h"
#include "GameEngine.h"
#include "ResourceManager.h"
#include "Time.h"

GameEngine::GameEngine()
{
	
}

GameEngine::~GameEngine()
{

}

void GameEngine::init(const std::string& window_name, int window_width, int window_height)
{
	//Setup the time class
	Time::StartUp();

	window_ = new sf::RenderWindow(sf::VideoMode(window_width, window_width), window_name);



	//sf::Texture* texture = new sf::Texture();
	//if (!texture->loadFromFile("awesomeface.png"))
	//{
	//	return exit(EXIT_FAILURE);
	//}

	//textures_.emplace_back(texture);

	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(ResourceManager::get_texture("awesomeface.png"));
	sprite->scale(0.5f, 0.5f);

	sprites_.emplace_back(sprite);
}

void GameEngine::run()
{
	while (window_->isOpen())
	{
		//Create delta for this frame
		Time::Update();
		
		sf::Event event;
		while(window_->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_->close();
		}

		process_input();

		const auto pos = sprites_.at(0)->getPosition();
		auto p_x = pos.x;
		auto p_y = pos.y;

		const auto tmp = p_x;

		const auto speed = 75;


		if (get_key(key_code::key_a) == key_status::hold)
		{
			p_x -= speed * delta_time_;
		}

		if (get_key(key_code::key_d) == key_status::hold)
		{
			p_x += speed * delta_time_;
		}

		if(get_key(key_code::key_w) == key_status::hold)
		{
			p_y -= speed * delta_time_;
		}

		if (get_key(key_code::key_s) == key_status::hold)
		{
			p_y += speed * delta_time_;
		}

		sprites_.at(0)->setPosition(p_x, p_y);

		std::cout << tmp << " - " << p_x << std::endl;


		render();
	}
}

key_status GameEngine::get_key(key_code key)
{
	return key_statuses_[static_cast<long long int>(key)];
}

void GameEngine::process_input()
{
	process_key_input(sf::Keyboard::W, key_code::key_w);
	process_key_input(sf::Keyboard::A, key_code::key_a);
	process_key_input(sf::Keyboard::S, key_code::key_s);
	process_key_input(sf::Keyboard::D, key_code::key_d);
}

void GameEngine::process_key_input(sf::Keyboard::Key gl_key, key_code key)
{
	if (sf::Keyboard::isKeyPressed(gl_key))
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
	else if (!sf::Keyboard::isKeyPressed(gl_key) && (key_statuses_[static_cast<unsigned long long>(key)] == key_status::pressed || key_statuses_[static_cast<unsigned long long>(key)] == key_status::hold))
	{
		key_statuses_[static_cast<unsigned long long>(key)] = key_status::lifted;
	}
	else
	{
		key_statuses_[static_cast<unsigned long long>(key)] = key_status::unpressed;
	}
}

void GameEngine::render()
{
	window_->clear(sf::Color::Black);

	for(const auto& s : sprites_)
	{
		window_->draw(*s);
	}

	window_->display();
}

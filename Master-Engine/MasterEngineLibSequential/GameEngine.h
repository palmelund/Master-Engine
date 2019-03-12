#pragma once

#include "SFML/Graphics.hpp"

#include <array>
#include "GameObject.h"
#include <queue>
#include <unordered_set>

#define LOG_DELTA_TIMES

class GameEngine
{
public:
	GameEngine() = delete;
	~GameEngine() = delete;
	static void init();
	static void run();

	static unsigned long long get_new_id();

	static  void Instantiate(GameObject*, sf::Vector2f);

	static void add_game_object(GameObject* game_object);
	static void add_collider(GameObject* game_object);
	static void remove_collider(GameObject* game_object);

	static void remove_game_object(GameObject* game_object);

	static std::unordered_set<GameObject*>& get_gamestate();
	static std::unordered_set<GameObject*>& get_destroyid_game_object();

private:
	static unsigned long long incremental_id_;
	static std::unordered_set<GameObject*> game_objects_;
	static std::unordered_set<GameObject*> destroyid_game_object_;
	static std::unordered_set<GameObject*> collision_game_object_;
#ifdef LOG_DELTA_TIMES
	static std::vector<float> delta_list_;
#endif
};

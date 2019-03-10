#pragma once
#include "GameObject.h"
#include <unordered_set>
#include <queue>


class GameState
{
public:
	GameState() = delete;
	~GameState() = delete;
	GameState(const GameState&) = delete;
	GameState(GameState&&) = delete;
	GameState& operator=(const GameState&) = delete;
	GameState& operator=(GameState&&) = delete;

	static unsigned long long get_new_id();

	static void add_game_object(GameObject* game_object);

	static void remove_game_object(GameObject* game_object);

	static std::unordered_set<GameObject*>& get_gamestate();
	static std::queue<GameObject*>& get_destroyid_game_object();

private:
	static unsigned long long incremental_id_;
	static std::unordered_set<GameObject*> game_objects_;
	static std::queue<GameObject*> destroyid_game_object_;

};

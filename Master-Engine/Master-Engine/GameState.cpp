#include "pch.h"
#include "GameState.h"

unsigned long long GameState::incremental_id_{};
std::unordered_set<GameObject*> GameState::game_objects_{};

unsigned long long GameState::get_new_id()
{
	return ++incremental_id_;
}

void GameState::add_game_object(GameObject* game_object)
{
	game_objects_.insert(game_object);
}

void GameState::remove_game_object(GameObject* game_object)
{
	game_objects_.erase(game_object);
}

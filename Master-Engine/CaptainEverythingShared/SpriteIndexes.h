#pragma once

namespace CaptainEverythingShared
{
	class SpriteIndexes
	{
	public:
		SpriteIndexes() = delete;
		constexpr static int sprite_width = 200;
		constexpr static int sprite_height = 200;

		constexpr static int player_sprite = 0;
		constexpr static int enemy_sprite = 1;
		constexpr static int gravity_well_sprite = 2;
		constexpr static int bullet_sprite = 3;
		constexpr static int shield_sprite = 4;
		constexpr static int background_sprite = 5;
		constexpr static int boss_sprite = 6;
	};
}
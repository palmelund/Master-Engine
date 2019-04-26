#pragma once
#include <sstream>
#include <thread>

namespace CaptainEverythingShared
{
	class Constants
	{
	public:
		Constants() = delete;

		constexpr static int screen_width = 800;
		constexpr static int screen_height = 500;

		constexpr static int boss_spawn_threshold = 50;

		constexpr static int player_bullet_size = 20;
		constexpr static int player_size = 20;
		constexpr static float player_speed = 900.0f;
		constexpr static float player_fire_rate = 0.8f;

		constexpr static int gravity_well_size = 160;
		constexpr static float gravity_well_pull_force = 1.0f;

		constexpr static int enemy_bullet_size = 20;
		constexpr static int enemy_size = 20;
		constexpr static float enemy_fire_rate = 1.3f;

		constexpr static float boss_shield_distance = 75.0f;
		constexpr static int boss_shield_speed = 100;
		constexpr static int boss_shield_size = 50;

		constexpr static int boss_size = 50;
		constexpr static int boss_shield_count = 3;

		constexpr static int background_element_size = 20;

		constexpr static float enemy_spawn_time = 1.2f;

		static int background_elements();

		static int gravity_wells();

		static void set_changeable_constants(char* background_elements, char* gravity_wells);
	private:
		static int background_element_count_;
		static int gravity_well_count_;

		constexpr static float record_time_start = 5.0f;
		constexpr static float record_time_end = 60.0f + record_time_start;
	};
}

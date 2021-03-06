#pragma once
#include <sstream>
#include <thread>

namespace CaptainEverythingShared
{
	class Constants
	{
	public:
		Constants() = delete;

		constexpr static int screen_width = 1200;
		constexpr static int screen_height = 900;

		constexpr static int boss_spawn_threshold = 50;

		constexpr static int player_bullet_size = 20;
		constexpr static int player_size = 20;
		constexpr static float player_acceleration = 900.0f;
		constexpr static float player_fire_rate = 0.8f;

		constexpr static int gravity_well_size = 160;
		constexpr static float gravity_well_pull_force = 1.0f;

		constexpr static int enemy_bullet_size = 20;
		constexpr static int enemy_size = 20;
		constexpr static float enemy_fire_rate = 3.0f;

		constexpr static float boss_shield_distance = 75.0f;
		constexpr static int boss_shield_speed = 100;
		constexpr static int boss_shield_size = 50;

		constexpr static int boss_size = 50;
		constexpr static int boss_shield_count = 3;

		constexpr static int background_element_size = 20;

		constexpr static float enemy_spawn_time = 1.2f;

		constexpr static float record_time_start =1.0f;
		constexpr static float record_time_end = 1000.0f + record_time_start;

		static int background_elements();

		static int gravity_wells();

		static int thread_count();

		static void set_changeable_constants(char* background_elements, char* gravity_wells, char* thread_count);
	private:
		static int background_element_count_;
		static int gravity_well_count_;
		static int thread_count_;
	};
}

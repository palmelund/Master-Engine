#include "pch.h"
#include "Constants.h"
using namespace CaptainEverythingShared;

int Constants::background_element_count_{ 300 };
int Constants::gravity_well_count_{ 1 };
int Constants::thread_count_{ static_cast<int>(std::thread::hardware_concurrency()) };
int Constants::test_duration_{ 60 };

int Constants::background_elements()
{
	return background_element_count_;
}

int Constants::gravity_wells()
{
	return gravity_well_count_;
}

int Constants::thread_count()
{
	return thread_count_;
}

int Constants::test_duration()
{
	return test_duration_;
}

void Constants::set_changeable_constants(char* background_elements, char* gravity_wells, char* thread_count, char* test_duration)
{
	std::istringstream background_elements_stream{ background_elements };
	background_elements_stream >> background_element_count_;

	std::istringstream gravity_wells_stream{ gravity_wells };
	gravity_wells_stream >> gravity_well_count_;

	std::istringstream test_duration_stream{ test_duration };
	test_duration_stream >> test_duration_;
	test_duration_ += record_time_start;

	std::istringstream thread_count_stream{thread_count};

	int tmp;

	thread_count_stream >> tmp;

	if(tmp != 0)
	{
		thread_count_ = tmp;
	}
}

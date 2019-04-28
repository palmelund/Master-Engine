// TestRunner.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>
#include <sstream>
#include <fstream>

std::string exe(const char* cmd)
{
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	return result;
}

int main()
{
	std::vector<std::string> res{};

	std::vector<int> test_sizes_single_core = { 30,300,1000 };
	std::vector<int> test_sizes_background_element = { 30,300,1000, 2000 };
	std::vector<int> test_sizes_gravity_well = { 1, 5, 10, 25 };
	std::vector<std::string> test_engine_names = { "CaptainEverythingSequential", "CaptainEverythingParallel", "CaptainEverythingAggregator" };

	int test_iterations = 5;

//#pragma region Single_Core
//	res.emplace_back("Single-Core test\n");
//	for (auto& engine : test_engine_names)
//	{
//		std::string start_string;
//		start_string += engine;
//		start_string += " START\n";
//		res.emplace_back(start_string);
//		for (auto test_size : test_sizes_single_core)
//		{
//			std::string test_title{};
//			test_title += engine;
//			test_title += " - ";
//			test_title += std::to_string(test_size);
//			test_title += " background elements\n";
//			res.emplace_back(test_title);
//
//			for (auto iteration = 0; iteration < test_iterations; iteration++)
//			{
//				std::string command{};
//				command += engine;
//				command += " ";
//				command += std::to_string(test_size);
//				command += " 1 1";
//
//				std::string result = exe(command.c_str());
//				res.emplace_back(result);
//			}
//		}
//	}
//#pragma endregion
#pragma region Background_element
	res.emplace_back("Background_element test\n");
	for (int i = 1; i < 3; i++)
	{
		std::string start_string;
		start_string += test_engine_names[i];
		start_string += " START\n";
		res.emplace_back(start_string);
		for (auto test_size : test_sizes_background_element)
		{
			std::string test_title{};
			test_title += test_engine_names[i];
			test_title += " - ";
			test_title += std::to_string(test_size);
			test_title += " background elements\n";
			res.emplace_back(test_title);

			for (auto iteration = 0; iteration < test_iterations; iteration++)
			{
				std::string command{};
				command += test_engine_names[i];
				command += " ";
				command += std::to_string(test_size);
				command += " 1 0";

				std::string result = exe(command.c_str());
				res.emplace_back(result);
			}

		}
	}
#pragma endregion
#pragma region Gravity_well
	res.emplace_back("Background_element test\n");
	for (int i = 0; i < 3; i++)
	{
		std::string start_string;
		start_string += test_engine_names[i];
		start_string += " START\n";
		res.emplace_back(start_string);
		for (auto test_size : test_sizes_gravity_well)
		{
			std::string test_title{};
			test_title += test_engine_names[i];
			test_title += " - ";
			test_title += std::to_string(test_size);
			test_title += " background elements\n";
			res.emplace_back(test_title);

			for (auto iteration = 0; iteration < test_iterations; iteration++)
			{
				std::string command{};
				command += test_engine_names[i];
				command += " 1000 ";
				command += std::to_string(test_size);
				command += " 0";

				std::string result = exe(command.c_str());
				res.emplace_back(result);
			}
		}
	}
#pragma endregion
	std::ofstream myfile;
	myfile.open("test_resualt.txt", std::ios::out | std::ios::trunc);

	for (auto& s : res)
	{
		myfile << s;
	}
	myfile.close();

	return EXIT_SUCCESS;
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

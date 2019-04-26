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
	std::vector<std::string> test_engine_names = { "CaptainEverythingSequential", "CaptainEverythingParallel", "CaptainEverythingAggregator" };

	int test_iterations = 1;

	res.emplace_back("Single-Core test");
	for (auto& engine : test_engine_names)
	{
		std::string start_string;
		start_string += engine;
		start_string += " START";
		res.emplace_back(start_string);
		for (auto test_size : test_sizes_single_core)
		{
			std::string test_title{};
			test_title += engine;
			test_title += " - ";
			test_title += std::to_string(test_size);
			test_title += " background elements";
			res.emplace_back(test_title);

			for (auto iteration = 0; iteration < test_iterations; iteration++)
			{
				std::string command{};
				command += engine;
				command += " ";
				command += std::to_string(test_size);
				command += " 1 1";

				std::string result = exe(command.c_str());
				res.emplace_back(result);
			}
		}
	}

	for (auto& s : res)
	{
		std::cout << s << std::endl;
	}

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

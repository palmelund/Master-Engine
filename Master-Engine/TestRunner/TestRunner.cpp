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

void write_results(std::string content, std::string file_name)
{
	std::ofstream myfile;
	myfile.open(file_name, std::ios::out | std::ios::app);


	myfile << content;

	myfile.close();
}

int main(int argc, char* argv[])
{
	std::vector<std::string> res{};

	std::vector<int> test_sizes_single_core = { 30,300,1000 };
	std::vector<int> test_sizes_background_element = { 30,300,1000, 2000 };
	std::vector<int> test_sizes_gravity_well = { 0, 1, 5, 10, 25, 100, 250 };
	std::vector<std::string> test_engine_names = { "CaptainEverythingSequential.exe", "CaptainEverythingParallel.exe", "CaptainEverythingAggregator.exe" };

	int test_iterations = 5;
	int current_iteration = 0;
	int max_iterations = (((test_sizes_background_element.size()*test_engine_names.size())+(test_engine_names.size()*test_sizes_gravity_well.size()))*test_iterations);

#pragma region Single_Core
	std::istringstream argument{argv[1]};
	int testing;
	argument >> testing;
	if (testing == 1)
	{
		max_iterations += (test_sizes_single_core.size()*test_engine_names.size()) * test_iterations;
		write_results("Single - Core test\n", "test_results.txt");

		for (auto& engine : test_engine_names)
		{
			std::string start_string;
			start_string += engine;
			start_string += " START\n";
			write_results(start_string, "test_results.txt");

			for (auto test_size : test_sizes_single_core)
			{
				std::string test_title{};
				test_title += engine;
				test_title += " - ";
				test_title += std::to_string(test_size);
				test_title += " background elements\n";
				write_results(test_title, "test_results.txt");
			
				for (auto iteration = 0; iteration < test_iterations; iteration++)
				{
					current_iteration++;
					const char base_string[] = "";
					char out_string[10];
					sprintf_s(out_string, " %d/%d", current_iteration, max_iterations);


					std::string command{};
					command += "start /wait /affinity 4 ";
					command += engine;
					command += " ";
					command += std::to_string(test_size);
					command += " 1 1 ";
					command += out_string;

					system(command.c_str());
				}
			}
		}
	}
	
#pragma endregion

#pragma region Background_element
	write_results("Background_element test\n", "test_results.txt");
	for (int i = 0; i < 3; i++)
	{
		

		std::string start_string;
		start_string += test_engine_names[i];
		start_string += " START\n";

		write_results(start_string, "test_results.txt");
		
		for (auto test_size : test_sizes_background_element)
		{

			std::string test_title{};
			test_title += test_engine_names[i];
			test_title += " - ";
			test_title += std::to_string(test_size);
			test_title += " background elements\n";
			write_results(test_title, "test_results.txt");
			

			for (auto iteration = 0; iteration < test_iterations; iteration++)
			{
				current_iteration++;
				const char base_string[] = "";
				char out_string[10];
				sprintf_s(out_string, " %d/%d", current_iteration, max_iterations);

				std::string command{};
				command += "start /wait ";
				command += test_engine_names[i];
				command += " ";
				command += std::to_string(test_size);
				command += " 0 0";
				command += out_string;
				command += " >> test_results.txt";

				system(command.c_str());

			}

		}
	}
#pragma endregion
#pragma region Gravity_well
	write_results("gravity_well test\n", "test_results.txt");
	for (int i = 0; i < 3; i++)
	{
		std::string start_string;
		start_string += test_engine_names[i];
		start_string += " START\n";
		write_results(start_string, "test_results.txt");
		for (auto test_size : test_sizes_gravity_well)
		{
			std::string test_title{};
			test_title += test_engine_names[i];
			test_title += " - ";
			test_title += std::to_string(test_size);
			test_title += " gravity_well\n";
			write_results(test_title, "test_results.txt");
			for (auto iteration = 0; iteration < test_iterations; iteration++)
			{
				current_iteration++;
				const char base_string[] = "";
				char out_string[10];
				sprintf_s(out_string, " %d/%d", current_iteration, max_iterations);


				std::string command{};
				command += test_engine_names[i];
				command += " 100 ";
				command += std::to_string(test_size);
				command += " 0";
				command += out_string;

				system(command.c_str());
			}
		}
	}
#pragma endregion

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

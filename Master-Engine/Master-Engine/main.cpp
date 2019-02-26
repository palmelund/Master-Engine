// Master-Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "GameEngine.h"
#include <thread>
#include "ThreadPool.h"

#define GENERATE_ASSIGNMENT_OPERATIONS(t,n) \
	private: \
		t generated_assignment_value_##t_##n_ = 0; \
		int generated_assignment_priority_##t_##n_ = INT_MIN; \
	public: \
		void operator=(t val) { \
			if(n == INT32_MIN + 1) { \
			return; \
			} \
			generated_assignment_value_##t_##n_ = val; \
			generated_assignment_priority_##t_##n_ = INT32_MIN; \
		} \
		void assign(##t val) { \
			if(##n == INT32_MIN + 1) { \
			return; \
			} \
			generated_assignment_value_##t_##n_ = val; \
			generated_assignment_priority_##t_##n_ = INT32_MIN; \
		} \
		void assign(t val, int priority) { \
			if(priority < generated_assignment_priority_##t_##n_) return; \
			generated_assignment_value_##t_##n_ = val; \
			generated_assignment_priority_##t_##n_ = priority; \
		}

void pp()
{
	std::cout << "0123456789" << std::endl;
}

struct m_int final {
GENERATE_ASSIGNMENT_OPERATIONS(int, val_)

public:
	m_int(int val) : val_(val) {}

	m_int(const m_int&) = default;
	m_int(m_int&&) noexcept = default;
	m_int& operator=(const m_int&) = default;
	m_int& operator=(m_int&&) noexcept = default;

	int get() const noexcept { return val_; }

	virtual ~m_int() = default;
private:
	int val_;
};

int main()
{
	ThreadPool::CreateThreadPool();
	std::vector<void(*)()> funcs{};

	for(auto i = 0; i < 10000; i++)
	{
		funcs.emplace_back(pp);
	}

	ThreadPool::AddJob(funcs);

	while (true)
	{
		
	}

	//GameEngine engine{};
	//engine.init("Master Engine", 800, 600);

	//engine.run();
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
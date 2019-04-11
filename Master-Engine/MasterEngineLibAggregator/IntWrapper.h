#pragma once
class IntWrapper
{
public:
	IntWrapper();
	~IntWrapper();

	void operator+=(const int& rhs);
	void operator*=(const int& rhs);

	void operator=(const int& rhs);
	void assign(const int& rhs, int priority);

	int get_value();
	void set_value(int);
private:
	int value_;
};


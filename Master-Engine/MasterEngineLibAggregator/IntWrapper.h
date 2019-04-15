#pragma once
class IntWrapper
{
public:
	IntWrapper();

	void operator+=(const int& rhs);
	void operator*=(const int& rhs);

	void operator=(const int& rhs);
	void assign(const int& rhs, int priority);

	int get_value() const;
	void set_value(int);
private:
	int value_;
};


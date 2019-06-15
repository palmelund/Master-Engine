#pragma once
#include "BaseWrapper.h"

class IntWrapper final : public BaseWrapper
{
public:
	IntWrapper();

	void operator+=(const int& rhs);
	void operator*=(const int& rhs);

	void operator=(const int& rhs);
	void assign(const int& rhs, int priority);
	void reset() override;

	int get_value() const;
	void set_value(int);
private:
	int value_;
};


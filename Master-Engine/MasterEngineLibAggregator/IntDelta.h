#pragma once
#include "BaseDelta.h"
#include "IntWrapper.h"
class IntDelta final :
	public BaseDelta
{
public:
	explicit IntDelta(IntWrapper*);

	void assign(int value, int priority);
	void addition(int value);
	void multiply(int value);

	void reduce(void*) override;
	void merge() override;
private:
	IntWrapper* original_value_;

	int additions_;
	int multiplications_;

	int assign_;
	int assign_priority_;
};


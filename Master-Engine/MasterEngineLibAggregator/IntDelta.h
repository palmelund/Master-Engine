#pragma once
#include "BaseDelta.h"
#include "BaseWrapper.h"
class IntDelta final :
	public BaseDelta
{
public:
	explicit IntDelta(BaseWrapper*);

	void assign(int value, int priority);
	void addition(int value);
	void multiply(int value);

	void reduce(void*) override;
	void merge() override;
private:

	int additions_;
	int multiplications_;

	int assign_;
	int assign_priority_;
};


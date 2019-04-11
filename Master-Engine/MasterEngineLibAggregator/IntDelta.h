#pragma once
#include "BaseDelta.h"
#include "IntWrapper.h"
class IntDelta :
	public BaseDelta
{
public:
	IntDelta(IntWrapper*);
	~IntDelta();

	void assign(int value, int priority);
	void addition(int value);
	void multiply(int value);

	void reduce(void*) override;
	void merge() override;
private:
	IntWrapper* orginal_value_;

	int additions_;
	int multiplys_;

	int assign_;
	int assing_priority_;
};


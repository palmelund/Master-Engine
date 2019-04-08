#pragma once
class BaseWrapper
{
public:
	BaseWrapper(void*);
	~BaseWrapper();

	void virtual reduce(void*) = 0;
	void virtual merge() = 0;
private:
	void* orginal_pointer_;
};


#pragma once
#include <vector>

template <class T>
class VectorWrapper
{
public:
	VectorWrapper();
	~VectorWrapper();

private:
	std::vector<T> value_;
};


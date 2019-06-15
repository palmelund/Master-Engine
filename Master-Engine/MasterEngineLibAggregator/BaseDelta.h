#pragma once
#include "BaseWrapper.h"

class BaseDelta
{
public:
	BaseDelta();
	BaseDelta(const BaseDelta&) = delete;
	BaseDelta(BaseDelta&&) = delete;
	BaseDelta& operator=(const BaseDelta&) = delete;
	BaseDelta& operator=(BaseDelta&&) = delete;
	virtual ~BaseDelta();

	void virtual reduce(void*) = 0;
	void virtual merge() = 0;

	BaseWrapper* original_value_;

private:
};


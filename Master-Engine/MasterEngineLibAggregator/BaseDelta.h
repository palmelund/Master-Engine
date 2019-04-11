#pragma once
class BaseDelta
{
public:
	BaseDelta();
	virtual ~BaseDelta();

	void virtual reduce(void*) = 0;
	void virtual merge() = 0;
private:
};


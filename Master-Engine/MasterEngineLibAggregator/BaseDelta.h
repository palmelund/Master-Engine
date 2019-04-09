#pragma once
class BaseDelta
{
public:
	BaseDelta();
	~BaseDelta();

	void virtual reduce(void*) = 0;
	void virtual merge() = 0;
private:
};


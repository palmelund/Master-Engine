#pragma once
#include "BaseDelta.h"
#include "Vector2Wrapper.h"

class Vector2Delta final : public BaseDelta
{
public:
	explicit Vector2Delta(Vector2Wrapper*);

	void addition(sf::Vector2f);
	void assign(sf::Vector2f, int);
	void reduce(void*) override;
	void merge() override;

private:
	Vector2Wrapper* original_value_;
	sf::Vector2f additions_;
	sf::Vector2f assign_;
	int assign_priority_;

};


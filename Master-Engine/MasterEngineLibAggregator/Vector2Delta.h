#pragma once
#include "BaseDelta.h"
#include <SFML/System/Vector2.hpp>
#include "BaseWrapper.h"

class Vector2Delta final : public BaseDelta
{
public:
	explicit Vector2Delta(BaseWrapper*);

	void addition(sf::Vector2f);
	void assign(sf::Vector2f, int);
	void reduce(void*) override;
	void merge() override;
	
private:
	
	sf::Vector2f additions_;
	sf::Vector2f assign_;
	int assign_priority_;

};


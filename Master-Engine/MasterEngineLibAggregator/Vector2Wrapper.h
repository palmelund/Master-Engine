#pragma once
#include <SFML/System/Vector2.hpp>
#include "BaseWrapper.h"
#include <map>
#include <thread>

class Vector2Delta;

class Vector2Wrapper final : public BaseWrapper
{
public:
	Vector2Wrapper();

	void operator+=(const sf::Vector2f& rhs);

	void operator=(const sf::Vector2f& rhs);

	void assign(const sf::Vector2f& rhs, int priority);
	void reset() override;
	sf::Vector2f get_vector() const;

	void set_vector(sf::Vector2f);

	std::map<std::thread::id, Vector2Delta*> local_delta_list;
private:
	sf::Vector2f value_;

};


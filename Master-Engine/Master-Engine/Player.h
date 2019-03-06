#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	Player(const std::string&);
	~Player();

	void update() override;
	void OnCollision(GameObject* collider) override;
private:
	sf::Vector2f velocity;
	int size_;
	sf::Vector2f rotate_vector(sf::Vector2f);

	template<
		typename T, //real type
		typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
	>
	static T clamp(T val, T minval, T maxval)
	{
		// Branchless SSE clamp.
		// return minss( maxss(val,minval), maxval );
		return std::min(std::max(val, minval), maxval);
	}
};


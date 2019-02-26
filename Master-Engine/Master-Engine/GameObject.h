#pragma once

class GameObject
{
public:
	explicit GameObject(bool requires_input);

	inline bool requires_input() const noexcept;


protected:
	~GameObject();

private:
	const bool requires_input_;
};


#pragma once

class Updatable
{
protected:
	~Updatable() = default;
private:
	virtual void update() = 0;
};

class GameObject : public Updatable
{
public:
	explicit GameObject(bool requires_input);

	inline bool requires_input() const noexcept;

protected:
	~GameObject();

private:

	bool requires_input_;
};


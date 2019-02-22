#pragma once
template<typename T>
struct wrapped_value
{
public:
	explicit wrapped_value(const T& value) noexcept : value_(value) {}
	T& get() const noexcept { return value_; }
private:
	T& value_;
};
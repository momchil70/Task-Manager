//Does not manage the memory! It is managed by the pool
#pragma once
#include <iostream>
#include "Date.h"

class OptionalDate {
private:
	const Date* value = nullptr;

public:
	OptionalDate() = default;

	void clear();

	OptionalDate& operator=(OptionalDate&& other) noexcept;
	OptionalDate& operator=(const OptionalDate& other);

	bool hasValue() const;
	const Date& getValue() const;
	void setValue(const Date* newValue);
};
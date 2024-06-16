#pragma once
#include "Date.h"
#include "Vector.hpp"


class DatePool
{
	Date* dates;
	int* referenceCounts;
	int count = 0;
	int capacity = 0;

	int find(const Date& d) const;

	DatePool();

	bool isFree(unsigned index) const;

	unsigned getFreeIndex() const;

	void resize(unsigned newCap);
	void free();

	~DatePool();
public:

	DatePool(const DatePool& dp) = delete;
	DatePool& operator=(const DatePool& dp) = delete;

	const Date& getDate(const String& date, const String& taskName);

	void removeDate(const Date& date, const String& taskName);

	static DatePool& getInstance();

};


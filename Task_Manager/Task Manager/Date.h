#pragma once
#include "String.h"
#include "Vector.hpp"

class Date
{
	String dayOfWeek;
	unsigned day;
	unsigned month;
	unsigned year;

	MyVector<String> names;

	void parseDate(const String& user_given);
public:
	Date() = default;

	Date(const String& user_given);

	friend std::ostream& operator<<(std::ostream& os, const Date& d);

	int getNamesSize() const;

	const String& getName(int index) const;

	void addName(const String& name);

	void removeName(const String& name);

	unsigned getDay() const;
	unsigned getMonth() const;
	unsigned getYear() const;

};

bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);

bool operator>=(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
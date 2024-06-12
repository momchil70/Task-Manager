#pragma once
#include "String.h"
#include "Vector.hpp"

class Date
{
	String about;

	MyVector<String> names;

	void getDayOfWeek(const String& user_given);
	void getYMD(const String& user_given);
public:
	Date() = default;

	Date(const String& user_given);

	friend std::ostream& operator<<(std::ostream& os, const Date& d);

	const String& getAbout() const;

	int getNamesSize() const;

	const String& getName(int index) const;

	void addName(const String& name);

	void removeName(const String& name);

};

bool operator==(const Date& lhs, const Date& rhs);

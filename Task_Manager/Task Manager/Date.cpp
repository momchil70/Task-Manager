#include <iomanip>
#include <sstream>
#include <ctime>
#include "Date.h"
#pragma warning(disable : 4996)

Date::Date(const String& user_given)
{
	parseDate(user_given);
}

void Date::addName(const String& name)
{
	int namesSize = names.size();
	for (int i = 0; i < namesSize; i++) {
		if (name == names[i]) throw std::exception("This name is already in that day!");
	}
	names.push_back(name);
}

void Date::removeName(const String& name)
{
	int index = 0;

	int namesSize = names.size();
	for (int i = 0; i < namesSize; i++) {
		if (name == names[i]) index = i;
	}
	names.erase(index);
}

unsigned Date::getDay() const
{
	return day;
}

unsigned Date::getMonth() const
{
	return month;
}

unsigned Date::getYear() const
{
	return year;
}

const String& Date::getName(int index) const
{
	return names[index];
}

int Date::getNamesSize() const
{
	return names.size();
}



std::ostream& operator<<(std::ostream& os, const Date& d)
{
	static const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	os << d.dayOfWeek << " " << d.day << " 00:00:00 " << months[d.month - 1] << " " << d.year;
	return os;
}


void Date::parseDate(const String& user_given) {
	static const char* days_of_week[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

	// Parse the input date string
	std::tm tm = {};
	std::istringstream ss(user_given.c_str());
	ss >> std::get_time(&tm, "%Y-%m-%d");

	// Set tm_isdst to -1 to let mktime determine if DST is in effect
	tm.tm_isdst = -1;

	// Convert to time_t
	std::time_t time = std::mktime(&tm);
	if (time == -1) {
		throw std::runtime_error("mktime failed!");
	}

	// Get the local time (tm struct) from the time_t
	std::tm* ptm = std::localtime(&time);
	if (ptm == nullptr) {
		throw std::runtime_error("localtime failed!");
	}

	dayOfWeek = days_of_week[ptm->tm_wday];
	day = ptm->tm_mday;
	month = ptm->tm_mon + 1; 
	year = ptm->tm_year + 1900;
}

bool operator==(const Date& lhs, const Date& rhs) {

	return (lhs.getDay() == rhs.getDay() && lhs.getMonth() == rhs.getMonth() && lhs.getYear() == rhs.getYear());
}

bool operator!=(const Date& lhs, const Date& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const Date& lhs, const Date& rhs)
{
	if (lhs.getYear() < rhs.getYear()) return true;

	else if (lhs.getYear() > rhs.getYear()) return false;

	else {
		if (lhs.getMonth() < rhs.getMonth()) {
			return true;
		}
		else if (lhs.getMonth() > rhs.getMonth()) {
			return false;
		}
		else {
			return lhs.getDay() < rhs.getDay();
		}
	}
}

bool operator>(const Date& lhs, const Date& rhs)
{
	if (lhs.getYear() > rhs.getYear()) return true;

	else if (lhs.getYear() < rhs.getYear()) return false;

	else {
		if (lhs.getMonth() > rhs.getMonth()) {
			return true;
		}
		else if (lhs.getMonth() < rhs.getMonth()) {
			return false;
		}
		else {
			return lhs.getDay() > rhs.getDay();
		}
	}
}

bool operator>=(const Date& lhs, const Date& rhs)
{
	return !(lhs < rhs);
}

bool operator<=(const Date& lhs, const Date& rhs)
{
	return !(lhs > rhs);
}

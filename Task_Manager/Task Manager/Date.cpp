#include <iomanip>
#include <sstream>
#include <ctime>
#include "Date.h"
#pragma warning(disable : 4996)

Date::Date(const String& user_given)
{
    getDayOfWeek(user_given);
    getYMD(user_given);
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

const String& Date::getAbout() const
{
    return about;
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
    os << d.about << std::endl;
    return os;
}

void Date::getDayOfWeek(const String& user_given)
{
    static const char* days_of_week[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

    std::string date_str = user_given.c_str();
    std::tm tm = {};
    std::istringstream ss(date_str);

    ss >> std::get_time(&tm, "%Y-%m-%d");

    if (ss.fail()) {
        throw std::exception("Failed to parse date!");
    }

    std::time_t time = std::mktime(&tm);
    if (time == -1) {
        throw std::exception("mktime failed!");
    }

    std::tm* ptm = std::localtime(&time);
    if (ptm == nullptr) {
        throw std::exception("localtime failed!");
    }

    about += days_of_week[ptm->tm_wday];
}


void Date::getYMD(const String& user_given) {
    std::string date_str = user_given.c_str();
    std::tm tm = {};
    std::istringstream ss(date_str);

    ss >> std::get_time(&tm, "%Y-%m-%d");

    std::time_t time = std::mktime(&tm);
    std::tm* ltm = std::localtime(&time);

    static const char* weekdays[] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
    static const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

    about = "";
    about += weekdays[ltm->tm_wday];
    about += " ";
    about += months[ltm->tm_mon];
    about += " ";

    // Convert day
    std::ostringstream day_ss;
    day_ss << ltm->tm_mday;
    about += day_ss.str().c_str();

    about += " 00:00:00 ";

    // Convert year
    std::ostringstream year_ss;
    year_ss << (ltm->tm_year + 1900);
    about += year_ss.str().c_str();
}

bool operator==(const Date& lhs, const Date& rhs) {
    
    return lhs.getAbout() == rhs.getAbout();
}
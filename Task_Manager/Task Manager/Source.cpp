#include <iostream>
#include "String.h"
#include "Date.h"
#include "User.h"
#include "System.h"

int main() {
    System s;
}


//#pragma warning(disable:4996)
//#include <iostream>
//#include <ctime>
//#include <iomanip>
//#include <sstream>
//
//std::string getFormattedDate() {
//    // Get current time
//    std::time_t now = std::time(nullptr);
//    std::tm* ltm = std::localtime(&now);
//
//    // Array of day and month names
//    const char* daysOfWeek[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
//    const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
//
//    // Format the date
//    std::ostringstream oss;
//    oss << daysOfWeek[ltm->tm_wday] << ", " << months[ltm->tm_mon] << " " << ltm->tm_mday << ", "
//        << "00:00:00, "
//        << 1900 + ltm->tm_year;
//
//    return oss.str();
//}
//
//int main() {
//    std::string formattedDate = getFormattedDate();
//    std::cout << formattedDate << std::endl;
//    return 0;
//}
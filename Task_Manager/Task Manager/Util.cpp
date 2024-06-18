#include "Util.h"

String getCurrentDate() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);

    char dateString[11];
    std::sprintf(dateString, "%04d-%02d-%02d",
        localTime->tm_year + 1900,
        localTime->tm_mon + 1,
        localTime->tm_mday);

    return String(dateString);
}
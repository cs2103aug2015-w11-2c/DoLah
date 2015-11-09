//@@author A0116722M
#include "TimeManager.h"

namespace DoLah {
    TimeManager::TimeManager() {
    }

    TimeManager::~TimeManager() {
    }

    std::tm TimeManager::copyDay(std::tm from, std::tm to) {
        to.tm_year = from.tm_year;
        to.tm_mon = from.tm_mon;
        to.tm_mday = from.tm_mday;

        return to;
    }

    bool TimeManager::isValidDate(std::tm date) {
        std::tm checkTime = date;
        std::mktime(&checkTime);
        if (checkTime.tm_year == -1 && checkTime.tm_mon == -1 && checkTime.tm_mday == -1) {
            throw std::invalid_argument("");
        }
        // IF mktime changes the time format, that means the input date was wrong!
        // ex. 31st April becomes 1st May
        if (date.tm_mday != checkTime.tm_mday
            || date.tm_mon != checkTime.tm_mon
            || date.tm_year != checkTime.tm_year) {
            return false;
        }
        return true;
    }

    std::tm TimeManager::getCurrentTime() {
        time_t t = time(0);
        std::tm current;
        localtime_s(&current, &t);
        
        return current;
    }

    int TimeManager::compareTime(std::tm startdate, std::tm enddate) {
        return difftime(mktime(&enddate), mktime(&startdate));
    }

}
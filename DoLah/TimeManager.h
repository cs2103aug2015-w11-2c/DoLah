#pragma once

#include <ctime>
#include <string>

namespace DoLah {
    /**
    * @class TimeManager.h TimeManager.h
    * @brief A library consists of general functions related to time manipulation in std::tm.
    *
    * These functions are widly used in parse component.
    */
    class TimeManager {
    public:
        TimeManager();
        ~TimeManager();

        static std::tm copyDay(std::tm, std::tm);
        
        /**
         * Check whether the given std::tm represents a valid date or not.
         * For example, 31st of April is an invalid date.
         * @param[in]   date Date to be evaluated.
         * return True is it is a valid date.
         */
        static bool isValidDate(std::tm);

        /**
         * Returns the current time according to the localtime setting in the system.
         * return Current time represented in std::tm format.
         */
        static std::tm getCurrentTime();

        /**
         * Compare the two times and return int value that represents the comparison result.
         * @param[in]   startdate Date that is supposed to be earlier.
         * @param[in]   enddate Date that is supposed to be later.
         * return Positive int represents startdate is earlier than enddate. Negative represents the opposite. 0 represents equal.
         */
        static int compareTime(std::tm startdate, std::tm enddate);
    };
}
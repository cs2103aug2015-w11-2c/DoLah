#pragma once

#include <ctime>
#include <string>

namespace DoLah {
    class TimeManager {
    public:
        TimeManager();
        ~TimeManager();

        static std::tm copyDay(std::tm, std::tm);
        
        // 31st of Feb is not valid
        static bool isValidDate(std::tm);

        static std::tm getCurrentTime();
        static int compareTime(std::tm startdate, std::tm enddate);
    };
}
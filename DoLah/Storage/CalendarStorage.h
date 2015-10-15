#pragma once
#include "Models/Calendar.h"
#include <fstream>

namespace DoLah {
    class CalendarStorage
    {
    public:
        CalendarStorage();
        ~CalendarStorage();

        static void save(const DoLah::Calendar &, const std::string &);
        static Calendar load(const std::string &);
    };
}


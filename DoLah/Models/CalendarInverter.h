#pragma once
#include <Models/Calendar.h>

namespace DoLah {
    class CalendarInverter {
    public:
        CalendarInverter();
        ~CalendarInverter();

        static void invertAdd(AbstractTask *, Calendar *);
        static void invertDelete(AbstractTask *, Calendar *);
        static void invertEdit(AbstractTask *, Calendar *);
        static void invertClear(std::vector<AbstractTask*>, Calendar *);
        static void invertSearch(std::vector<AbstractTask*> **, std::string, Calendar *);
        static void invertDone(AbstractTask *, Calendar *);

    private:
    };
}
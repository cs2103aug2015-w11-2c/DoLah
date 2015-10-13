#pragma once
#include "Models/Calendar.h"


class CalendarBuilder
{
public:
    CalendarBuilder();
    ~CalendarBuilder();

    static DoLah::Calendar buildSimpleCalendar();
};


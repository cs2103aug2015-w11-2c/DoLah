#include "stdafx.h"
#include "CalendarBuilder.h"
#include "TaskBuilder.h"


CalendarBuilder::CalendarBuilder()
{
}


CalendarBuilder::~CalendarBuilder()
{
}

DoLah::Calendar CalendarBuilder::buildSimpleCalendar()
{
    DoLah::Calendar calendar;
    for (int i = 0; i < 5; i++) {
        calendar.addTask(TaskBuilder::buildFloatingTask());
        calendar.addTask(TaskBuilder::buildEventTask());
        calendar.addTask(TaskBuilder::buildDeadlineTask());
    }
    return calendar;
}

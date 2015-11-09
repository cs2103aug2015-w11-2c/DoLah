//@@collate A0116631M
#include "stdafx.h"
#include "CalendarBuilder.h"
#include "TaskBuilder.h"


CalendarBuilder::CalendarBuilder() {
}


CalendarBuilder::~CalendarBuilder() {
}

DoLah::Calendar CalendarBuilder::buildSimpleCalendar() {
    DoLah::Calendar calendar;
    bool toggleDone = false;
    for (int i = 0; i < 5; i++) {
        calendar.addTask(TaskBuilder::buildFloatingTask(toggleDone));
        toggleDone = !toggleDone;
        calendar.addTask(TaskBuilder::buildEventTask(toggleDone));
        toggleDone = !toggleDone;
        calendar.addTask(TaskBuilder::buildDeadlineTask(toggleDone));
        toggleDone = !toggleDone;
    }
    return calendar;
}

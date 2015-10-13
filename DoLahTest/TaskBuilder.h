#pragma once
#include "Models/Task.h"

class TaskBuilder
{
public:
    TaskBuilder();
    ~TaskBuilder();

    static DoLah::FloatingTask buildFloatingTask();
    static DoLah::DeadlineTask buildDeadlineTask();
    static DoLah::EventTask buildEventTask();
private:
    static int buildIndex;
};

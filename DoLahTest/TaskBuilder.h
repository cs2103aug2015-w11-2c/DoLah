//@@author A0116631M
#pragma once
#include "Models/Task.h"

class TaskBuilder
{
public:
    TaskBuilder();
    ~TaskBuilder();

    static DoLah::FloatingTask* buildFloatingTask(bool=false);
    static DoLah::DeadlineTask* buildDeadlineTask(bool=false);
    static DoLah::EventTask* buildEventTask(bool=false);
private:
    static int buildIndex;
};

#pragma once
#include "Task.h"

class AbstractTaskFactory {
public:
    virtual DoLah::AbstractTask* makeTask() = 0;
};

class FloatingTaskFactory {
public:
    DoLah::AbstractTask* makeTask() {
        return new DoLah::FloatingTask;
    }
};

class DeadlineTaskFactory {
public:
    DoLah::AbstractTask* makeTask() {
        return new DoLah::DeadlineTask;
    }
};

class EventTaskFactory {
public:
    DoLah::AbstractTask* makeTask() {
        return new DoLah::EventTask;
    }
};
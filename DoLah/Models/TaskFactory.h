#pragma once
#include "Task.h"

class AbstractTaskFactory {
public:
    virtual DoLah::AbstractTask* makeTask() = 0;
};

class FloatingTaskFactory {
public:
    static DoLah::AbstractTask* makeTask() {
        return new DoLah::FloatingTask;
    }
};

class DeadlineTaskFactory {
public:
    static DoLah::AbstractTask* makeTask() {
        return new DoLah::DeadlineTask;
    }
};

class EventTaskFactory {
public:
    static DoLah::AbstractTask* makeTask() {
        return new DoLah::EventTask;
    }
};
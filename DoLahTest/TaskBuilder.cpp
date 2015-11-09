#include "stdafx.h"
#include "TaskBuilder.h"
#include <string>
#include <ctime>

TaskBuilder::TaskBuilder(){
}


//@@collate A0116631M
TaskBuilder::~TaskBuilder(){
}

DoLah::FloatingTask* TaskBuilder::buildFloatingTask(bool isDone) {
    std::stringstream name;
    name << "Floating Task " << TaskBuilder::buildIndex;
    std::stringstream desc;
    desc << "A task description for floating task " << TaskBuilder::buildIndex;
    
    DoLah::FloatingTask* task = new DoLah::FloatingTask;
    task->setId(TaskBuilder::buildIndex);
    task->setName(name.str());
    task->setDescription(desc.str());
    task->setDone(isDone);
    return task;
}

DoLah::EventTask* TaskBuilder::buildEventTask(bool isDone) {
    std::stringstream name;
    name << "Event Task " << TaskBuilder::buildIndex;
    std::stringstream desc;
    desc << "A task description for event task " << TaskBuilder::buildIndex;
    std::time_t t = std::time(NULL);
    
    std::tm later = *std::localtime(&t);
    later.tm_hour += 20;
    std::mktime(&later);

    std::tm tomorrow = later;
    tomorrow.tm_hour += 25;
    std::mktime(&tomorrow);

    DoLah::EventTask* task = new DoLah::EventTask;
    task->setId(TaskBuilder::buildIndex);
    task->setName(name.str());
    task->setDescription(desc.str());
    task->setStartDate(later);
    task->setEndDate(tomorrow);
    task->setDone(isDone);
    return task;
}

DoLah::DeadlineTask* TaskBuilder::buildDeadlineTask(bool isDone) {
    std::stringstream name;
    name << "Deadline Task " << TaskBuilder::buildIndex;
    std::stringstream desc;
    desc << "A task description for deadline task " << TaskBuilder::buildIndex;
    // std::chrono::system_clock::time_point dueDate = std::chrono::system_clock::now() + std::chrono::hours(10);
    
    std::time_t t = std::time(NULL);
    std::tm dueDate = *std::localtime(&t);
    dueDate.tm_mon += 10;
    std::mktime(&dueDate);

    DoLah::DeadlineTask* task = new DoLah::DeadlineTask;
    task->setId(TaskBuilder::buildIndex);
    task->setName(name.str());
    task->setDescription(desc.str());
    task->setDueDate(dueDate);
    task->setDone(isDone);
    return task;
}

int TaskBuilder::buildIndex = 0;
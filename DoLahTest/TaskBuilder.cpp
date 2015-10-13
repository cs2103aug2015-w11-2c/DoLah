#include "stdafx.h"
#include "TaskBuilder.h"
#include <string>
#include <ctime>

TaskBuilder::TaskBuilder()
{
}


TaskBuilder::~TaskBuilder()
{
}

DoLah::FloatingTask TaskBuilder::buildFloatingTask() {
    std::stringstream name;
    name << "Floating Task " << TaskBuilder::buildIndex;
    std::stringstream desc;
    desc << "A task description for floating task " << TaskBuilder::buildIndex;
    
    DoLah::FloatingTask task;
    task.setId(TaskBuilder::buildIndex);
    task.setName(name.str());
    task.setDescription(desc.str());
    task.setDone(false);
    return task;
}

DoLah::EventTask TaskBuilder::buildEventTask() {
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

    DoLah::EventTask task;
    task.setId(TaskBuilder::buildIndex);
    task.setName(name.str());
    task.setDescription(desc.str());
    task.setStartDate(later);
    task.setEndDate(tomorrow);
    task.setDone(false);
    return task;
}

DoLah::DeadlineTask TaskBuilder::buildDeadlineTask() {
    std::stringstream name;
    name << "Deadline Task " << TaskBuilder::buildIndex;
    std::stringstream desc;
    desc << "A task description for deadline task " << TaskBuilder::buildIndex;
    // std::chrono::system_clock::time_point dueDate = std::chrono::system_clock::now() + std::chrono::hours(10);
    
    std::time_t t = std::time(NULL);
    std::tm dueDate = *std::localtime(&t);
    dueDate.tm_mon += 10;
    DoLah::DeadlineTask task;
    task.setId(TaskBuilder::buildIndex);
    task.setName(name.str());
    task.setDescription(desc.str());
    task.setDueDate(dueDate);
    task.setDone(false);
    return task;
}

int TaskBuilder::buildIndex = 0;
#include "Task.h"

namespace DoLah {
    using namespace std::chrono;

    Task::Task() {}
    Task::~Task() {}

    void Task::setName(std::string name) {
        this->name = name;
    }

    std::string Task::getName() {
        return this->name;
    }

    void Task::setDescription(std::string description) {
        this->description = description;
    }

    std::string Task::getDescription() {
        return this->description;
    }

    void Task::setDone(bool done) {
        this->done = done;
    }

    bool Task::isDone() {
        return this->done;
    }

    void Task::setId(int id) {
        this->id = id;
    }

    int Task::getId() {
        return this->id;
    }
    EventTask::EventTask() { }
    EventTask::~EventTask() { }

    void EventTask::setEndDate(system_clock::time_point datetime) {
        this->endDate = datetime;
    }

    system_clock::time_point EventTask::getEndDate() {
        return this->endDate;
    }

    void EventTask::setStartDate(system_clock::time_point datetime) {
        this->startDate = datetime;
    }

    system_clock::time_point EventTask::getStartDate() {
        return this->startDate;
    }
}
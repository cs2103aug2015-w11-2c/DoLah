#include "Task.h"

namespace DoLah {

    using namespace std::chrono;

    EventTask::EventTask() {}
    EventTask::~EventTask() {}

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
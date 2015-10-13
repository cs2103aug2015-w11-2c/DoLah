#include "Task.h"

namespace DoLah {

    using namespace std::chrono;

    EventTask::EventTask() {}
    EventTask::~EventTask() {}

    void EventTask::setEndDate(std::tm datetime) {
        this->endDate = datetime;
    }

    std::vector<std::tm> EventTask::getDates() {
        return {this->startDate, this->endDate};
    }

    std::tm EventTask::getEndDate() {
        return this->endDate;
    }

    void EventTask::setStartDate(std::tm datetime) {
        this->startDate = datetime;
    }

    std::tm EventTask::getStartDate() {
        return this->startDate;
    }
}
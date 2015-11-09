//@@author A0116631M
#include "Task.h"

namespace DoLah {

    using namespace std::chrono;

    EventTask::EventTask() {}
    EventTask::~EventTask() {}

    void EventTask::setEndDate(std::tm datetime) {
        this->endDate = datetime;
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

    void EventTask::updateExpired() {
        if (!isExpired()) {
            std::tm current = TimeManager::getCurrentTime();
            setExpired(TimeManager::compareTime(this->endDate, current) > 0);
        }
    }
}
//@@author A0116631M
#include "Task.h"

namespace DoLah {

    using namespace std::chrono;

    DeadlineTask::DeadlineTask() {}
    DeadlineTask::~DeadlineTask() {}

    void DeadlineTask::setDueDate(std::tm datetime) {
        this->dueDate = datetime;
    }

    std::tm DeadlineTask::getDueDate() {
        return this->dueDate;
    }

    void DeadlineTask::updateExpired() {
        if (!isExpired()) {
            std::tm current = TimeManager::getCurrentTime();
            setExpired(TimeManager::compareTime(this->dueDate, current) > 0);
        }
    }
}
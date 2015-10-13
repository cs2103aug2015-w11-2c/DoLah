#include "Task.h"

namespace DoLah {

    using namespace std::chrono;

    DeadlineTask::DeadlineTask() {}
    DeadlineTask::~DeadlineTask() {}

    void DeadlineTask::setDueDate(std::tm datetime) {
        this->dueDate = datetime;
    }

    std::vector<std::tm> DeadlineTask::getDates() {
        return {this->dueDate};
    }

    std::tm DeadlineTask::getDueDate() {
        return this->dueDate;
    }
}
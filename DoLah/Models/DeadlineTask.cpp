#include "Task.h"

namespace DoLah {

    using namespace std::chrono;

    DeadlineTask::DeadlineTask() {}
    DeadlineTask::~DeadlineTask() {}

    void DeadlineTask::setDueDate(system_clock::time_point datetime) {
        this->dueDate = datetime;
    }

    system_clock::time_point DeadlineTask::getDueDate() {
        return this->dueDate;
    }
}
#include "Task.h"

namespace DoLah {

    AbstractTask::AbstractTask() {}
    AbstractTask::~AbstractTask() {}

    void AbstractTask::setName(std::string name) {
        this->name = name;
    }

    std::string AbstractTask::getName() {
        return this->name;
    }

    void AbstractTask::setDescription(std::string description) {
        this->description = description;
    }

    std::string AbstractTask::getDescription() {
        return this->description;
    }

    void AbstractTask::setDone(bool done) {
        this->done = done;
    }

    bool AbstractTask::isDone() {
        return this->done;
    }

    void AbstractTask::setId(int id) {
        this->id = id;
    }

    int AbstractTask::getId() {
        return this->id;
    }

}
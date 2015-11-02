#include "Task.h"
#include "TaskFactory.h"

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

    void AbstractTask::setTags(std::vector<std::string> tags) {
        this->tags = tags;
    }

    std::vector<std::string> AbstractTask::getTags() {
        return this->tags;
    }

    void AbstractTask::setExpired(bool expired) {
        this->expired = expired;
    }

    bool AbstractTask::isExpired() {
        return this->expired;
    }

    void AbstractTask::updateExpired() {
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
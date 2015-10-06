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
    ISerializable * FloatingTask::serialize(const std::string& data) {
        return NULL;
    }
    std::string FloatingTask::deserialize() {
        return std::string();
    }
    ISerializable * DeadlineTask::serialize(const std::string& data) {
        return NULL;
    }
    std::string DeadlineTask::deserialize() {
        return std::string();
    }
    ISerializable * EventTask::serialize(const std::string& data) {
        return NULL;
    }
    std::string EventTask::deserialize() {
        return std::string();
    }

}
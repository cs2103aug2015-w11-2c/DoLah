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

    void AbstractTask::setTags(std::vector<std::string> tags) {
        this->tags = tags;
    }

    std::vector<std::string> AbstractTask::getTags() {
        return this->tags;
    }

    void AbstractTask::setDone(bool done) {
        this->done = done;
    }

    bool AbstractTask::isDone() {
        return this->done;
    }

    std::vector<std::tm> AbstractTask::getDates() {
        return {};
    }

    std::string AbstractTask::toString() {
        std::string out = "";
        out += this->name + "; [";
        for (size_t i = 0; i < tags.size(); i++) {
            out += tags.at(i);
            if (i < tags.size()-1) {
                out += ",";
            }
        }
        out += "]";
        return out;
    }

    void AbstractTask::setId(int id) {
        this->id = id;
    }

    int AbstractTask::getId() {
        return this->id;
    }


}
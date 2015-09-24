#include "Task.h"

namespace DoLah {

    Task::Task() {}
    Task::~Task() {}

    void Task::setName(std::string name) {
        this->name = name;
    }

    std::string Task::getName() {
        return this->name;
    }

    void Task::setDescription(std::string description) {
        this->description = description;
    }

    std::string Task::getDescription() {
        return this->description;
    }

    void Task::setDone(bool done) {
        this->done = done;
    }

    bool Task::isDone() {
        return this->done;
    }

    void Task::setId(int id) {
        this->id = id;
    }

    int Task::getId() {
        return this->id;
    }

}
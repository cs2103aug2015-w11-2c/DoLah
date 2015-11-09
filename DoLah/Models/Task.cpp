//@@author A0116631M
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

    void AbstractTask::addTag(std::string tag) {
        this->tags.push_back(tag);
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

    void AbstractTask::setIndex(int index) {
        this->index = index;
    }

    int AbstractTask::getIndex() {
        return this->index;
    }

    //@@author A0111275R
    // Check if first < second
    bool AbstractTask::taskCompare(AbstractTask* first, AbstractTask* second) {
        if (typeid(*second) == typeid(FloatingTask)) {
            //case: floating task vs floating task
            if (typeid(*first) == typeid(FloatingTask)) {
                return first->getName().compare(second->getName()) < 0;
            }
            //case: non-floating task vs floating task
            return true;
        }
        else if (typeid(*first) == typeid(FloatingTask)) {
            //case: floating task vs non-floating task
            return false;
        }
        else {
            std::vector<std::tm> firstDates = getDates(first);
            std::vector<std::tm> secondDates = getDates(second);

            int diff = TimeManager::compareTime(firstDates[0], secondDates[0]);
            if (diff != 0) {
                return diff > 0;
            }
            else {
                return first->getName().compare(second->getName()) < 0;
            }
        }
    }

    //@@author A0116722M
    std::vector<std::tm> AbstractTask::getDates(AbstractTask *it) {
        std::vector<std::tm> dates;

        DoLah::FloatingTask* floatingTask = dynamic_cast<DoLah::FloatingTask*>(it);
        DoLah::EventTask* eventTask = dynamic_cast<DoLah::EventTask*>(it);
        DoLah::DeadlineTask* deadlineTask = dynamic_cast<DoLah::DeadlineTask*>(it);

        if (eventTask != NULL) {
            dates.push_back(eventTask->getEndDate());
            dates.push_back(eventTask->getStartDate());
        }

        if (deadlineTask != NULL) {
            dates.push_back(deadlineTask->getDueDate());
        }

        return dates;
    }
}
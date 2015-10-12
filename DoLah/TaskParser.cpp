#include "TaskParser.h"

namespace DoLah {
    TaskParser::TaskParser() {
    }


    TaskParser::~TaskParser() {
    }

    AbstractTask* TaskParser::parseTask(std::vector<std::string> inputArr) {
        std::vector<std::tm> dates = TaskTokenizer::findDate(inputArr);
        std::vector<std::string> tags = TaskTokenizer::findTags(inputArr);
        std::string description = TaskTokenizer::findDescription(inputArr);

        if (dates.size() == 1) {
            DeadlineTask* task = new DeadlineTask();
            task->setName(description);
            task->setTags(tags);
            task->setDueDate(dates.at(0));
            return task;
        } else if (dates.size() == 2) {
            EventTask* task = new EventTask();
            task->setName(description);
            task->setTags(tags);
            task->setStartDate(dates.at(0));
            task->setEndDate(dates.at(1));
            return task;
        }

        FloatingTask* task = new FloatingTask();
        task->setName(description);
        task->setTags(tags);
        return task;
    }
}


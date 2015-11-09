#pragma once

#include "Models/Task.h"
#include "TaskTokenizer.h"

namespace DoLah {
    class TaskParser {
    public:
        TaskParser();
        ~TaskParser();

        /**
         * Convert input string vector list into a task object
         * @param[in]   inputArr String vector list to be converted into a task object
         * @return Parsed task object
         */
        static AbstractTask* parseTask(std::vector<std::string>);
    };
}
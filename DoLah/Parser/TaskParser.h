#pragma once

#include "Models/Task.h"
#include "TaskTokenizer.h"

namespace DoLah {
    class TaskParser {
    public:
        TaskParser();
        ~TaskParser();

        // parseTask is used by parseAdd and parseEdit
        static AbstractTask* parseTask(std::vector<std::string>);
    };
}
#include "Command.h"

namespace DoLah {
    SetDoneTaskCommand::SetDoneTaskCommand(int taskIndex) : taskIndex(taskIndex) {}
    SetDoneTaskCommand::~SetDoneTaskCommand() {}
    void SetDoneTaskCommand::execute() {
        this->calendar->setDoneTask(this->taskIndex);
    };
}


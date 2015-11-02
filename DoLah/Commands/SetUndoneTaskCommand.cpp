#include "Command.h"

namespace DoLah {
    SetUndoneTaskCommand::SetUndoneTaskCommand(int taskIndex) : taskIndex(taskIndex) { }

    SetUndoneTaskCommand::~SetUndoneTaskCommand() { }

    void SetUndoneTaskCommand::execute() {
        this->calendar->setDoneTask(this->taskIndex, false);
    };
}
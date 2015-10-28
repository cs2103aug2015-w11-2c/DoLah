#include "Command.h"

namespace DoLah {
    SetDoneTaskCommand::SetDoneTaskCommand(int taskIndex) : taskIndex(taskIndex) {
    
    }
    
    SetDoneTaskCommand::~SetDoneTaskCommand() {
    
    }
    
    void SetDoneTaskCommand::execute() {
        this->calendar->setDoneTask(this->taskIndex);
    };

    void SetDoneTaskCommand::revert() {
        this->calendar->setDoneTask(this->calendar->getDoneList().size()-1);
    }
}


#include "Command.h"

namespace DoLah {
    SetDoneTaskCommand::SetDoneTaskCommand() {

    }

    SetDoneTaskCommand::SetDoneTaskCommand(int taskIndex) : taskIndex(taskIndex) {
    
    }
    
    SetDoneTaskCommand::~SetDoneTaskCommand() {
    
    }
    
    void SetDoneTaskCommand::execute() {
        this->oldTask = this->calendar->getTask(taskIndex);
        this->calendar->setDoneTask(this->taskIndex);
    };

    void SetDoneTaskCommand::revert() {
        CalendarInverter::invertDone(oldTask, calendar);
    }
}


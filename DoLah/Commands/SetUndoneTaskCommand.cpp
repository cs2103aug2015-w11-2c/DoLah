#include "Command.h"

namespace DoLah {
    //public
    SetUndoneTaskCommand::SetUndoneTaskCommand(int taskIndex) : taskIndex(taskIndex) {
    }

    SetUndoneTaskCommand::~SetUndoneTaskCommand() {
    }

    void SetUndoneTaskCommand::execute() {
        this->oldTask = this->calendar->getDoneList()[this->taskIndex];
        this->calendar->setDoneTask(this->taskIndex, false);
    };

    void SetUndoneTaskCommand::revert() {
        CalendarInverter::invertDone(oldTask, calendar);
    }

    //private
}
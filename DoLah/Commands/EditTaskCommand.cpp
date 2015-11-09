//@@collate A0111275R
#include "Command.h"

namespace DoLah {
    //public

    EditTaskCommand::EditTaskCommand(int index, DoLah::AbstractTask* targetTask) {
        taskIndex = index;
        task = targetTask;
    }

    EditTaskCommand::~EditTaskCommand() {

    }

    void EditTaskCommand::execute() {
        this->oldTask = calendar->getTask(taskIndex);
        this->calendar->updateTask(taskIndex, task);
    }

    void EditTaskCommand::revert() {
        CalendarInverter::invertEdit(oldTask, task, calendar);
    }

    //protected
}
#include "Command.h"

namespace DoLah {
	//public
	DeleteTaskCommand::DeleteTaskCommand() {

	}

	DeleteTaskCommand::DeleteTaskCommand(int index) {
		taskIndex = index;
	}

	DeleteTaskCommand::~DeleteTaskCommand() {

	}

	void DeleteTaskCommand::execute() {
        this->oldTask = this->calendar->getTask(taskIndex);
		this->calendar->deleteTask(taskIndex);
	}
    
    void DeleteTaskCommand::revert() {
        CalendarInverter::invertDelete(oldTask, calendar);
    }

	//private
}
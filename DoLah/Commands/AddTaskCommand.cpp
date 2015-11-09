//@@collate A0111275R
#include "Command.h"

namespace DoLah {
	//public

	AddTaskCommand::AddTaskCommand() {

	}

	AddTaskCommand::AddTaskCommand(DoLah::AbstractTask* newTask) {
		this->task = newTask;
	}

	AddTaskCommand::~AddTaskCommand() {

	}

	void AddTaskCommand::execute() {
		calendar->addTask(task);
	}

    void AddTaskCommand::revert() {
        CalendarInverter::invertAdd(task, calendar);
    }

	//protected
}
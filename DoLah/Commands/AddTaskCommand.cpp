#include "Command.h"

namespace DoLah {
	//public

	AddTaskCommand::AddTaskCommand() {

	}

	AddTaskCommand::AddTaskCommand(DoLah::AbstractTask* newTask) {
		task = newTask;
	}

	AddTaskCommand::~AddTaskCommand() {

	}

	void AddTaskCommand::execute() {
		calendar->addTask(task);
	}

	//protected
}
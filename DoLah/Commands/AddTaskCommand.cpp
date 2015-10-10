#include "Command.h"

namespace DoLah {
	//public

	AddTaskCommand::AddTaskCommand() {

	}

	AddTaskCommand::AddTaskCommand(DoLah::AbstractTask* task) {
		task = task;
	}

	AddTaskCommand::~AddTaskCommand() {

	}

	void AddTaskCommand::execute() {
		calendar.addTask(task);
	}

	//protected
}
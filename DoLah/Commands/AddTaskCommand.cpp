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

	void AddTaskCommand::setCalendar(DoLah::Calendar cal) {
		calendar = cal;
	}

	void AddTaskCommand::execute() {
		calendar.addTask(task);
	}

	//protected
}
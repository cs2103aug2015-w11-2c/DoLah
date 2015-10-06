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

	void DeleteTaskCommand::setCalendar(DoLah::Calendar cal) {
		calendar = cal;
	}

	void DeleteTaskCommand::execute() {
		calendar.deleteTask(taskIndex);
	}

	//private
}
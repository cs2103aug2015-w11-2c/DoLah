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
		calendar.deleteTask(taskIndex);
	}

	//private
}
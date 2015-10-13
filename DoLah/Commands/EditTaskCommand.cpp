#include "Command.h"

namespace DoLah {
	//public

	EditTaskCommand::EditTaskCommand() {

	}

	EditTaskCommand::EditTaskCommand(int index, DoLah::AbstractTask* targetTask) {
		taskIndex = index;
		task = targetTask;
	}

	EditTaskCommand::~EditTaskCommand() {

	}

    void EditTaskCommand::execute() {
		this->calendar.updateTask(taskIndex, task);
	}

	//protected
}
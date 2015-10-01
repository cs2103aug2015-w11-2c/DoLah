#include "Command.h"

namespace DoLah {
	//public

	EditTaskCommand::EditTaskCommand() {

	}

	EditTaskCommand::~EditTaskCommand() {

	}

	EditTaskCommand::EditTaskCommand(Calendar* cal, DoLah::AbstractTask* tk) {
		targetTask = tk;
		calendar = cal;
	}

	DoLah::AbstractTask* EditTaskCommand::getTargetTask() {
		return targetTask;
	}

	void EditTaskCommand::setTargetTask(DoLah::AbstractTask* task) {
		targetTask = task;
	}

	void EditTaskCommand::execute() {
		//TODO
	}

	//protected
}
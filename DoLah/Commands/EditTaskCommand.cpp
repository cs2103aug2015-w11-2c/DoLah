#include "Command.h"

namespace DoLah {
	//public

	EditTaskCommand::EditTaskCommand() {

	}

	EditTaskCommand::EditTaskCommand(int taskIndex, DoLah::AbstractTask* targetTask) {
		task = targetTask;

	}

	EditTaskCommand::~EditTaskCommand() {

	}

	DoLah::AbstractTask* EditTaskCommand::getTargetTask() {
		return task;
	}

	DoLah::Calendar EditTaskCommand::getCalendar() {
		return calendar;
	}

	void EditTaskCommand::setTargetTask(DoLah::AbstractTask* targetTask) {
		task = task;
	}

	void EditTaskCommand::setCalendar(DoLah::Calendar cal) {
		calendar = cal;
	}

	void EditTaskCommand::execute() {
		calendar.updateTask(task);
	}

	//protected
}
#include "Command.h"

namespace DoLah {
	//public

	EditTaskCommand::EditTaskCommand() {

	}

	EditTaskCommand::~EditTaskCommand() {

	}

	EditTaskCommand::EditTaskCommand(DoLah::Calendar cal, DoLah::AbstractTask* task) {
		targetTask = task;
		calendar = cal;
	}

	DoLah::AbstractTask* EditTaskCommand::getTargetTask() {
		return targetTask;
	}

	DoLah::Calendar EditTaskCommand::getCalendar() {
		return calendar;
	}

	void EditTaskCommand::setTargetTask(DoLah::AbstractTask* task) {
		targetTask = task;
	}

	void EditTaskCommand::setCalendar(DoLah::Calendar cal) {
		calendar = cal;
	}

	void EditTaskCommand::execute() {
		calendar.updateTask(targetTask);
	}

	//protected
}
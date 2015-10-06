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

	DoLah::AbstractTask* AddTaskCommand::getTask() {
		return task;
	}

	DoLah::Calendar AddTaskCommand::getCalendar() {
		return calendar;
	}

	void AddTaskCommand::setTask(DoLah::AbstractTask* task) {
		task = task;
	}

	void AddTaskCommand::setCalendar(DoLah::Calendar cal) {
		calendar = cal;
	}

	void AddTaskCommand::execute() {
		calendar.addTask(task);
	}

	//protected
}
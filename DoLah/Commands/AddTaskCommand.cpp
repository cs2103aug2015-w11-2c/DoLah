#include "Command.h"

namespace DoLah {
	//public

	AddTaskCommand::AddTaskCommand() {

	}

	AddTaskCommand::~AddTaskCommand() {

	}

	AddTaskCommand::AddTaskCommand(DoLah::Calendar cal, DoLah::AbstractTask* task) {
		newTask = task;
		calendar = cal;
	}

	DoLah::AbstractTask* AddTaskCommand::getNewTask() {
		return newTask;
	}

	DoLah::Calendar AddTaskCommand::getCalendar() {
		return calendar;
	}

	void AddTaskCommand::setNewTask(DoLah::AbstractTask* task) {
		newTask = task;
	}

	void AddTaskCommand::setCalendar(DoLah::Calendar cal) {
		calendar = cal;
	}

	void AddTaskCommand::execute() {

	}

	//protected
}
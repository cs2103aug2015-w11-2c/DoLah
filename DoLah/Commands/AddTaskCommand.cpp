#include "Command.h"

namespace DoLah {
	//public

	AddTaskCommand::AddTaskCommand() {

	}

	AddTaskCommand::AddTaskCommand(DoLah::AbstractTask* newTask) {
		task = newTask;
	}

	AddTaskCommand::~AddTaskCommand() {

	}

	AbstractTask* AddTaskCommand::getTask() {
		return task;
	}

	void AddTaskCommand::setCalendar(DoLah::Calendar* cal) {
		calendar = cal;
	}

	void AddTaskCommand::execute() {
		calendar->addTask(task);
	}

	//protected
}
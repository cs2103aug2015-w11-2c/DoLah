#include "Command.h"

namespace DoLah {
	//public

	AddTaskCommand::AddTaskCommand() {

	}

	AddTaskCommand::~AddTaskCommand() {

	}

	AddTaskCommand::AddTaskCommand(DoLah::Calendar* cal, DoLah::AbstractTask* task) {
		newTask = task;
		calendar = cal;
	}

	DoLah::AbstractTask* AddTaskCommand::getNewTask() {
		return newTask;
	}

	void AddTaskCommand::setNewTask(DoLah::AbstractTask* task) {
		newTask = task;
	}

	void AddTaskCommand::execute() {

	}

	//protected
}
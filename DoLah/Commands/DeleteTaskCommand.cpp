#include "Command.h"

namespace DoLah {
	//public
	DeleteTaskCommand::DeleteTaskCommand() {

	}

	DeleteTaskCommand::~DeleteTaskCommand() {

	}

	int DeleteTaskCommand::getTargetId() {
		return targetId;
	}

	DoLah::Calendar DeleteTaskCommand::getCalendar() {
		return calendar;
	}

	void DeleteTaskCommand::setTargetId(int id) {
		targetId = id;
	}

	void DeleteTaskCommand::setCalendar(DoLah::Calendar cal) {
		calendar = cal;
	}

	void DeleteTaskCommand::execute() {
		calendar.deleteTask(targetId);
	}

	//private
}
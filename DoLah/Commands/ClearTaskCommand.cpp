#include "Command.h"

namespace DoLah {
	//public
	ClearTaskCommand::ClearTaskCommand() {

	}
	
	ClearTaskCommand::~ClearTaskCommand() {

	}

	DoLah::Calendar ClearTaskCommand::getCalendar() {
		return calendar;
	}

	void ClearTaskCommand::setCalendar(DoLah::Calendar cal) {
		calendar = cal;
	}

	void ClearTaskCommand::execute() {
		calendar.clearTasks();
	}

	//private
}
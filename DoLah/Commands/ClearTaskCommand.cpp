#include "Command.h"

namespace DoLah {
	//public
	ClearTaskCommand::ClearTaskCommand() {

	}

	ClearTaskCommand::~ClearTaskCommand() {

	}

	void ClearTaskCommand::setCalendar(DoLah::Calendar cal) {
		calendar = cal;
	}

	void ClearTaskCommand::execute() {
		calendar.clearTasks();
	}

	//private
}
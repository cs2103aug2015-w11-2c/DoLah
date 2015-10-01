#include "Command.h"

namespace DoLah {
	AbstractCommand::AbstractCommand() {
	}

	AbstractCommand::~AbstractCommand() {
	}

	void AbstractCommand::setCalendar(Calendar* cal) {
		calendar = cal;
	}

	Calendar* AbstractCommand::getCalendar() {
		return calendar;
	}

	void execute() {

	}
}

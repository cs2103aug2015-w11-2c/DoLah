//@@collate A0111275R
#include "Command.h"

namespace DoLah {
	//public
	ClearTaskCommand::ClearTaskCommand() {

	}

	ClearTaskCommand::~ClearTaskCommand() {

	}

	void ClearTaskCommand::execute() {
        this->oldTaskList = this->calendar->getAllTaskList();
		this->calendar->clearTasks();
	}

    void ClearTaskCommand::revert() {
        CalendarInverter::invertClear(oldTaskList, calendar);
    }

	//private
}
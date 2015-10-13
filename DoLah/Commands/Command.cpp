#include "Command.h"

namespace DoLah {

	ITaskCommand::~ITaskCommand() {
	}

    void ITaskCommand::setCalendar(DoLah::Calendar& calendar)
    {
        this->calendar = calendar;
    }
}

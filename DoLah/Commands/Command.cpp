//@@collate A0111275R
#include "Command.h"

namespace DoLah {

	AbstractCommand::~AbstractCommand() {
	}

    void AbstractCommand::setCalendar(DoLah::Calendar * calendar){
        this->calendar = calendar;
    }
}

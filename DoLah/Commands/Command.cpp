//@@collate A0111275R
#include "Command.h"

namespace DoLah {
    //public
	AbstractCommand::~AbstractCommand() {
	}

    void AbstractCommand::setCalendar(DoLah::Calendar * calendar){
        this->calendar = calendar;
    }
}

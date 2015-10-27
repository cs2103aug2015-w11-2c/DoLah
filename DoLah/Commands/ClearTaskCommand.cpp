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
        for (int i = 0; i < this->oldTaskList.size(); i++) {
            this->calendar->addTask(this->oldTaskList.at(i));
        }
    }

	//private
}
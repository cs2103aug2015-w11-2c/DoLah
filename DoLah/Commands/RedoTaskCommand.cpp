#include "Command.h"

namespace DoLah {
	//public
	RedoTaskCommand::RedoTaskCommand() {

	}

	RedoTaskCommand::~RedoTaskCommand() {

	}

	void RedoTaskCommand::execute() {
        AbstractCommand * command = this->calendar->getCmdHistory()->redo();
        command->execute();
	}

    void RedoTaskCommand::revert() {
        //unimplemented
    }

	//private
}
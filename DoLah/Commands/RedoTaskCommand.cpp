#include "Command.h"

namespace DoLah {
	//public
	RedoTaskCommand::RedoTaskCommand() {

	}

	RedoTaskCommand::~RedoTaskCommand() {

	}

	void RedoTaskCommand::execute() {
        AbstractCommand * command = this->commHistory->redo();
        command->execute();
	}

	//private
}
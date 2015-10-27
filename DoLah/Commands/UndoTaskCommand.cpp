#include "Command.h"

namespace DoLah {
	//public
	UndoTaskCommand::UndoTaskCommand() {

	}

	UndoTaskCommand::~UndoTaskCommand() {

	}

	void UndoTaskCommand::execute() {
        AbstractCommand * command = this->commHistory->undo();
        command->revert();
	}

	//private
}
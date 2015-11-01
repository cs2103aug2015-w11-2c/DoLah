#include "Command.h"

namespace DoLah {
	//public
	UndoTaskCommand::UndoTaskCommand() {

	}

	UndoTaskCommand::~UndoTaskCommand() {

	}

	void UndoTaskCommand::execute() {
        AbstractCommand * command = this->calendar->getCmdHistory()->undo();
        command->revert();
	}

    void UndoTaskCommand::revert() {
        //we actually want to just skip past this
        this->execute();
    }

	//private
}
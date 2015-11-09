//@@author A0111275R
#include "Command.h"

namespace DoLah {
    // data
    std::string UndoTaskCommand::ILLEGAL_FUNCTION_CALL_MESSAGE = "A function was called on UndoTaskCommand illegally!";
    
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
        //this should never be called
        throw std::logic_error(ILLEGAL_FUNCTION_CALL_MESSAGE);
    }

	//private
}
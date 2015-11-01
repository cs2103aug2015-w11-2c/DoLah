#include "Command.h"

namespace DoLah {
    //error messages
    std::string RedoTaskCommand::ILLEGAL_FUNCTION_CALL_MESSAGE = "A function was called on RedoTaskCommand illegally!";

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
        //this should never be called
        throw std::logic_error(ILLEGAL_FUNCTION_CALL_MESSAGE);
    }

	//private
}
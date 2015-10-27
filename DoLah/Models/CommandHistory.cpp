#include "CommandHistory.h"

namespace DoLah {
	//public
    CommandHistory::CommandHistory() {

	}

    CommandHistory::~CommandHistory() {

	}

    void CommandHistory::addToUndoStack(AbstractCommand * command) {
        this->undoStack.push(command);
    }

    AbstractCommand * CommandHistory::undo() {
        AbstractCommand * command = this->undoStack.top();
        this->undoStack.pop();
        this->redoStack.push(command);
        return command;
    }

	AbstractCommand * CommandHistory::redo() {
        AbstractCommand * command = this->redoStack.top();
        this->redoStack.pop();
        this->undoStack.push(command);
        return command;
	}

	//private
}
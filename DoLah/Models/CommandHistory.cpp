//@@collate A0111275R
#include "CommandHistory.h"

namespace DoLah {
    //data
    std::string CommandHistory::INVALID_UNDO_CALL_MESSAGE = "There is nothing to undo!";
    std::string CommandHistory::INVALID_REDO_CALL_MESSAGE = "There is nothing to redo!";

	//public
    CommandHistory::CommandHistory() {

	}

    CommandHistory::~CommandHistory() {

	}

    int CommandHistory::getUndoStackSize() const {
        return this->undoStack.size();
    }

    int CommandHistory::getRedoStackSize() const {
        return this->redoStack.size();
    }

    void CommandHistory::addToUndoStack(AbstractCommand * command) {
        this->undoStack.push(command);
    }

    AbstractCommand * CommandHistory::undo() {
        if (this->undoStack.empty()) {
            throw std::out_of_range(INVALID_UNDO_CALL_MESSAGE);
        }

        AbstractCommand * command = this->undoStack.top();
        this->undoStack.pop();
        this->redoStack.push(command);
        return command;
    }

	AbstractCommand * CommandHistory::redo() {
        if (this->redoStack.empty()) {
            throw std::out_of_range(INVALID_REDO_CALL_MESSAGE);
        }

        AbstractCommand * command = this->redoStack.top();
        this->redoStack.pop();
        this->undoStack.push(command);
        return command;
	}

	//private
}
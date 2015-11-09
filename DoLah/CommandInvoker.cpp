//@@author A0111275R
#include "CommandInvoker.h"

namespace DoLah {
    //public
    CommandInvoker::CommandInvoker() {

    }

    CommandInvoker::~CommandInvoker() {

    }

    void CommandInvoker::setCmdHistory(CommandHistory* history) {
        this->cmdHistory = history;
    }

    void CommandInvoker::process(AbstractCommand * command) {
        command->execute();
        if (!checkIfExcludedCommandType(command)) {
            cmdHistory->addToUndoStack(command);
        }
    }

    //private
    bool CommandInvoker::checkIfExcludedCommandType(AbstractCommand * command) {
        if (typeid(*command) == typeid(SearchTaskCommand)) {
            return true;
        }
        if (typeid(*command) == typeid(SearchDateTaskCommand)) {
            return true;
        }
        if (typeid(*command) == typeid(UndoTaskCommand)) {
            return true;
        }
        if (typeid(*command) == typeid(RedoTaskCommand)) {
            return true;
        }

        return false;
    }
}
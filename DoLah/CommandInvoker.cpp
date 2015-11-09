//@@collate A0111275R
#include "CommandInvoker.h"

namespace DoLah {

    CommandInvoker::CommandInvoker() {

    }

    CommandInvoker::~CommandInvoker() {

    }

    void CommandInvoker::setCmdHistory(CommandHistory* history) {
        this->cmdHistory = history;
    }

    bool CommandInvoker::checkIfExcludedCommandType(AbstractCommand * command) {
        if (typeid(*command) == typeid(RedoTaskCommand)) {
            return true;
        }
        if (typeid(*command) == typeid(UndoTaskCommand)) {
            return true;
        }
        if (typeid(*command) == typeid(SearchTaskCommand)) {
            return true;
        }
        if (typeid(*command) == typeid(SearchDateTaskCommand)) {
            return true;
        }

        return false;
    }

    void CommandInvoker::process(AbstractCommand * command) {
        command->execute();
        if (!checkIfExcludedCommandType(command)) {
            cmdHistory->addToUndoStack(command);
        }
    }
}
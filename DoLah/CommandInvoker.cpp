#include "CommandInvoker.h"

namespace DoLah {

    CommandInvoker::CommandInvoker() {

    }

    CommandInvoker::~CommandInvoker() {

    }

    void CommandInvoker::setCmdHistory(CommandHistory* history) {
        this->cmdHistory = history;
    }

    void CommandInvoker::process(AbstractCommand * command) {
        command->execute();
        if (typeid(*command) != typeid(RedoTaskCommand) && typeid(*command) != typeid(UndoTaskCommand)) {
            if (typeid(*command) != typeid(SearchTaskCommand)) {
                cmdHistory->addToUndoStack(command);
            }
        }
    }
}
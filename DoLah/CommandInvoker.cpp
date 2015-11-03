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
        RedoTaskCommand * checkRedo = (RedoTaskCommand *) command;
        UndoTaskCommand * checkUndo = (UndoTaskCommand *) command;
        if (typeid(*command) != typeid(RedoTaskCommand) && typeid(*command) != typeid(UndoTaskCommand)) {
            cmdHistory->addToUndoStack(command);
        }
    }
}
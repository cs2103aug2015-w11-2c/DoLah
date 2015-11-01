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
        cmdHistory->addToUndoStack(command);
    }
}
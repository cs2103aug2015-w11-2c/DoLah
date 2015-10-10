#include "CommandInvoker.h"

namespace DoLah {

    CommandInvoker::CommandInvoker() {

    }


    CommandInvoker::~CommandInvoker() {

    }

    void CommandInvoker::process(ITaskCommand *command) {
        command->execute();
    }
}
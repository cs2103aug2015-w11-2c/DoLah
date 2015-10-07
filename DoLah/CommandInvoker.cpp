#include "CommandInvoker.h"

namespace DoLah {

    CommandInvoker::CommandInvoker() {

    }


    CommandInvoker::~CommandInvoker() {

    }

    static void CommandInvoker::process(ITaskCommand* command) {
        command->execute();
    }
}

#include "CommandInvoker.h"

namespace DoLah {

    CommandInvoker::CommandInvoker() {

    }


    CommandInvoker::~CommandInvoker() {

    }

    void CommandInvoker::process(AbstractCommand *command) {
        command->execute();
    }
}
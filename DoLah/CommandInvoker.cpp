#include "CommandInvoker.h"



CommandInvoker::CommandInvoker()
{
}


CommandInvoker::~CommandInvoker()
{
}

void CommandInvoker::process(const DoLah::ITaskCommand& command) {
    command.execute();
}
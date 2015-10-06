#include "CommandInvoker.h"



CommandInvoker::CommandInvoker()
{
}


CommandInvoker::~CommandInvoker()
{
}

void CommandInvoker::process(DoLah::ITaskCommand& command) {
    command.execute();
}
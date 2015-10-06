#pragma once
#include "Commands/Command.h"

class CommandInvoker
{
public:
    CommandInvoker();
    ~CommandInvoker();

    static void process(const DoLah::ITaskCommand&);
};


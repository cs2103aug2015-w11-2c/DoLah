#pragma once
#include <stdio.h>
#include <iostream>
#include "Commands/Command.h"
#include "Models/CommandHistory.h"

namespace DoLah {

    class CommandInvoker
    {
    public:
        CommandInvoker();
        ~CommandInvoker();
        void process(ITaskCommand*);

    private:
        CommandHistory history;
    };

}
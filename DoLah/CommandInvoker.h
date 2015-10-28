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
        void setCmdHistory(CommandHistory*);
        void process(AbstractCommand*);

    private:
        CommandHistory* cmdHistory;
    };

}
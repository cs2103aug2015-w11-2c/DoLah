
#include <stdio.h>
#include <iostream>
#include "Commands/Command.h"

namespace DoLah {

    class CommandInvoker
    {
    public:
        CommandInvoker();
        ~CommandInvoker();
        static void process(DoLah::ITaskCommand*);

    };

};

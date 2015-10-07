#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "Commands/Command.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include "Models/Calendar.h"
#include "CommandParser.h"
#include "Models/Calendar.h"
#include "CommandInvoker.h"

namespace DoLah{
    class DoLahClient
    {
    public:
        DoLahClient();
        ~DoLahClient();
        void parseAndProcessCommand(std::string);
        void save();
        void load();

    private:
        std::string settingsFile;
        std::string storageFile;
        Calendar calendar;
    };
}


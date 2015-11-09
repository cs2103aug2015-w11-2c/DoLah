#pragma once

#include <stdio.h>
#include <vector>
#include <stack>
#include <fstream>
//#include "Models/Task.h"
#include "Models/Calendar.h"
#include "CommandInvoker.h"
#include "Config/ConfigurationManager.h"

namespace DoLah {

    class DoLahClient {
    public:
        DoLahClient();
        ~DoLahClient();
        void parseAndProcessCommand(std::string);
        Calendar getCalendar() const;
        void setStorageLocation(std::string);
        void setTheme(int);
        void restart();
    private:
        Configuration config;
        std::string settingsFile;
        DoLah::Calendar calendar;
        DoLah::CommandInvoker commandInvoker;
	};
}


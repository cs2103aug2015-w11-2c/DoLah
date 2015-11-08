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
        std::string getStorageLocation();
        void setStorageLocation(std::string);
    private:
        Configuration config;
        std::string settingsFile;
        DoLah::Calendar calendar;
        DoLah::CommandInvoker commandInvoker;
	};
}


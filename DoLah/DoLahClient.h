#pragma once

#include <vector>
#include <fstream>
#include "Commands/Command.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include "TaskCommandParser.h"
#include "Calendar.h"
#include "CalendarProcessor.h"

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
    CalendarProcessor processor;
    TaskCommandParser parser;
};
}


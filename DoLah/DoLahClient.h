#pragma once
<<<<<<< HEAD
#include <stdio.h>
#include <iostream>
#include <string>
#include "TaskCommandParser.h"
#include "Calendar.h"
#include "CalendarProcessor.h"

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

=======

#include <vector>
#include <stack>
#include <string>
#include <fstream>
#include "Models/Task.h"
#include "Commands/Command.h"

namespace DoLah {

	class DoLahClient {
	public:
		DoLahClient();

		void parseAndProcessCommand(std::string line);

	private:
	};
}
>>>>>>> 161c5e565b91c9582f05fe3195de50a1664b0d34

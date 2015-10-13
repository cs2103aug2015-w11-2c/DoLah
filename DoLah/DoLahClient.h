#pragma once

#include <stdio.h>
#include <vector>
#include <stack>
#include <fstream>
//#include "Models/Task.h"
#include "Models/Calendar.h"

namespace DoLah {

	class DoLahClient {
	public:
		DoLahClient();
        ~DoLahClient();
        void parseAndProcessCommand(std::string);
        void save();
        void load();

    private:
        std::string settingsFile;
        std::string storageFile;
        DoLah::Calendar calendar = DoLah::Calendar();
	};
}


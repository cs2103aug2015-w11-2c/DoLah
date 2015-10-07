#pragma once

#include <vector>
#include <stack>
#include <string>
#include <fstream>

#include "CommandParser.h"

#include "Models/Task.h"
#include "Commands/Command.h"

namespace DoLah {

	class DoLahClient {
	public:
		DoLahClient();

		void parseAndProcessCommand(std::string line);
        void save();
        void load();

	private:
        std::string settingFile;
        std::string storeFile;
        DoLah::Calendar calendar;
	};
}

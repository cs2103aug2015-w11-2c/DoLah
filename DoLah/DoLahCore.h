#pragma once

#include <vector>
#include <stack>
#include <string>
#include <fstream>
#include "Models/Task.h"
#include "Commands\Command.h"

namespace DoLah {

	class ITaskCommand;
	class ITokenObject;

	class DoLahCore {
	public:
		DoLahCore(std::string settings, std::string storage);

		//std::vector<std::string> DoLahCore::DoLah(std::string line);
		//DoLah::ITaskCommand* parseTaskCommand(std::vector<ITokenObject>);
		/*void save();
		void load();*/

		//std::vector<DoLah::Task> taskList;
		//std::stack<DoLah::ITaskCommand, DoLah::ITaskCommand> redoStack;
		//std::stack<DoLah::ITaskCommand, DoLah::ITaskCommand> undoStack;

	private:
		std::string settingsFile, storageFile;
	};
}

#pragma once

#include <vector>
#include <stack>
#include "Models/Task.h"

namespace DoLah {

	class ITaskCommand;

	class DoLahCore {
	public:
		DoLah::ITaskCommand* parseTaskCommand(std::vector<std::string>);
		void save();
		void load();
	private:
		std::string settingsFile, storageFile;
		std::vector<DoLah::Task> taskList;
		std::stack<DoLah::ITaskCommand,DoLah::ITaskCommand> redoStack;
		std::stack<DoLah::ITaskCommand,DoLah::ITaskCommand> undoStack;
	};
}
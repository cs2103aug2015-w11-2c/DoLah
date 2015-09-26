#pragma once

#include <vector>
#include <string>
#include "..\Models\Task.h"

namespace DoLah {

	class ITokenObject;

	class ITaskCommand {
	public:
		ITaskCommand(std::vector<ITokenObject>);
		void execute();
	protected:
		std::vector<ITokenObject> tokenVector;
		std::vector<DoLah::Task> * taskList;
		virtual void virtualmethod() = 0;
	};

	class AddTaskCommand : protected ITaskCommand {
		//AddTaskCommand(std::vector<ITokenObject> tokenVector);
		void execute();
	};

	class EditTaskCommand : public ITaskCommand {
		//EditTaskCommand(std::vector<ITokenObject> tokenVector);
		void execute();
	};

	class DeleteTaskCommand : public ITaskCommand {
		//DeleteTaskCommand(std::vector<ITokenObject> tokenVector);
		void execute();
	};
	class ClearTaskCommand : public ITaskCommand {
		//ClearTaskCommand(std::vector<ITokenObject> tokenVector);
		void execute();
	};

	class UndoTaskCommand : public ITaskCommand {
		UndoTaskCommand(std::vector<ITokenObject> tokenVector);
		void execute();
	};

	class RedoTaskCommand : public ITaskCommand {
		RedoTaskCommand(std::vector<ITokenObject> tokenVector);
		void execute();
	};

	class SearchTaskCommand : public ITaskCommand {
		SearchTaskCommand(std::vector<ITokenObject> tokenVector);
		void execute();
	};
}
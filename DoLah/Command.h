#pragma once

#include <vector>
#include <string>
#include "Models\Task.h"

namespace DoLah {

	class ITokenObject;
	std::vector<DoLah::Task> * taskList;

	class ITaskCommand {
	public:
		ITaskCommand(std::vector<ITokenObject>);
		void execute();
	protected:
		std::vector<ITokenObject> tokenVector;
		virtual void virtualmethod() = 0;
	};

	class AddTaskCommand : public ITaskCommand {};
	class EditTaskCommand : public ITaskCommand {};
	class DeleteTaskCommand : public ITaskCommand {};
	class ClearTaskCommand : public ITaskCommand {};
	class UndoTaskCommand : public ITaskCommand {};
	class RedoTaskCommand : public ITaskCommand {};
	class SearchTaskCommand : public ITaskCommand {};
}
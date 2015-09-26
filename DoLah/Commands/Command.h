#pragma once

#include <vector>
#include <string>

namespace DoLah {
	class ITaskCommand {
	public:
		ITaskCommand(std::vector<std::string>);
		void execute();
	protected:
		std::vector<std::string> tokenVector;
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
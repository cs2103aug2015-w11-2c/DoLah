#pragma once

#include <vector>
#include <string>
#include "..\Models\Task.h"

namespace DoLah {

	class Calendar;

	class AbstractCommand {
	public:
		AbstractCommand();
		virtual ~AbstractCommand() = 0;

		void setCalendar(Calendar* cal);
		Calendar* getCalendar();

		void execute();

	protected:
		Calendar* calendar;
	};

	class AddTaskCommand : public AbstractCommand {
	public:
		//AddTaskCommand(DoLah::AbstractTask* task);
		AddTaskCommand();
		AddTaskCommand(Calendar* cal, DoLah::AbstractTask* task);
		~AddTaskCommand();

		DoLah::AbstractTask* getTask();
		void setTask(DoLah::AbstractTask * tk);
		void execute();
	protected:
		DoLah::AbstractTask* task;
	};

	class EditTaskCommand : public AbstractCommand {
		//EditTaskCommand(std::vector<ITokenObject> tokenVector);
		void execute();
	};

	class DeleteTaskCommand : public AbstractCommand {
		//DeleteTaskCommand(std::vector<ITokenObject> tokenVector);
		void execute();
	};
	class ClearTaskCommand : public AbstractCommand {
		//ClearTaskCommand(std::vector<ITokenObject> tokenVector);
		void execute();
	};

	class UndoTaskCommand : public AbstractCommand {
		//UndoTaskCommand(std::vector<ITokenObject> tokenVector);
		void execute();
	};

	class RedoTaskCommand : public AbstractCommand {
		//RedoTaskCommand(std::vector<ITokenObject> tokenVector);
		void execute();
	};

	class SearchTaskCommand : public AbstractCommand {
		//SearchTaskCommand(std::vector<ITokenObject> tokenVector);
		void execute();
	};
}
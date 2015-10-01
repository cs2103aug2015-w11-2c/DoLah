#pragma once

#include <vector>
#include <string>
#include "..\Models\Task.h"
#include "..\CommandReceiver\Calendar.h"

namespace DoLah {

	class AbstractCommand {
	public:
		AbstractCommand();
		virtual ~AbstractCommand() = 0;

		void setCalendar(DoLah::Calendar * cal);
		DoLah::Calendar* getCalendar();

		void execute();

	protected:
		DoLah::Calendar * calendar;
	};

	class AddTaskCommand : public AbstractCommand {
	public:
		AddTaskCommand();
		AddTaskCommand(DoLah::Calendar* cal, DoLah::AbstractTask* task);
		~AddTaskCommand();

		DoLah::AbstractTask* getNewTask();
		void setNewTask(DoLah::AbstractTask *);
		void execute();

	private:
		DoLah::AbstractTask* newTask;
	};

	class EditTaskCommand : public AbstractCommand {
	public:
		EditTaskCommand();
		EditTaskCommand(DoLah::Calendar* cal, DoLah::AbstractTask * tk);
		~EditTaskCommand();

		DoLah::AbstractTask* getTargetTask();
		void setTargetTask(DoLah::AbstractTask *);
		void execute();

	private:
		DoLah::AbstractTask* targetTask;
	};

	class DeleteTaskCommand : public AbstractCommand {
	public:
		DeleteTaskCommand();
		~DeleteTaskCommand();

		int getTargetId();
		void setTargetId(int);
		void execute();

	private:
		int targetId;
	};

	class ClearTaskCommand : public AbstractCommand {
	public:
		ClearTaskCommand();
		~ClearTaskCommand();

		void execute();

	private:
	};

	class UndoTaskCommand : public AbstractCommand {
	public:
		UndoTaskCommand();
		~UndoTaskCommand();

		void execute();
	
	private:
	};

	class RedoTaskCommand : public AbstractCommand {
	public:
		RedoTaskCommand();
		~RedoTaskCommand();

		void execute();

	private:
	};

	class SearchTaskCommand : public AbstractCommand {
	public:
		SearchTaskCommand();
		~SearchTaskCommand();

		std::string getQuery();
		void setQuery(std::string);
		void execute();

	private:
		std::string query;
	};
}
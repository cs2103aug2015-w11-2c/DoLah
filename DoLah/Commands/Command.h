#pragma once

#include <vector>
#include <string>
#include "Models/Task.h"
#include "Models/Calendar.h"

namespace DoLah {

	class ITaskCommand {
	public:
		ITaskCommand();
		virtual ~ITaskCommand() = 0;

		void execute();
	private:
	};

	class AddTaskCommand : public ITaskCommand {
	public:
		AddTaskCommand();
		AddTaskCommand(DoLah::Calendar cal, DoLah::AbstractTask* task);
		~AddTaskCommand();

		DoLah::AbstractTask* getNewTask();
		DoLah::Calendar getCalendar();

		void setNewTask(DoLah::AbstractTask *);
		void setCalendar(DoLah::Calendar cal);

		void execute();

	private:
		DoLah::AbstractTask* newTask;
		DoLah::Calendar calendar;
	};

	class EditTaskCommand : public ITaskCommand {
	public:
		EditTaskCommand();
		EditTaskCommand(DoLah::Calendar cal, DoLah::AbstractTask * tk);
		~EditTaskCommand();

		DoLah::AbstractTask* getTargetTask();
		DoLah::Calendar getCalendar();

		void setTargetTask(DoLah::AbstractTask *);
		void setCalendar(DoLah::Calendar cal);

		void execute();

	private:
		DoLah::AbstractTask* targetTask;
		DoLah::Calendar calendar;
	};

	class DeleteTaskCommand : public ITaskCommand {
	public:
		DeleteTaskCommand();
		~DeleteTaskCommand();

		int getTargetId();
		DoLah::Calendar getCalendar();

		void setTargetId(int);
		void setCalendar(DoLah::Calendar cal);

		void execute();

	private:
		int targetId;
		DoLah::Calendar calendar;
	};

	class ClearTaskCommand : public ITaskCommand {
	public:
		ClearTaskCommand();
		~ClearTaskCommand();

		DoLah::Calendar getCalendar();

		void setCalendar(DoLah::Calendar cal);

		void execute();

	private:
		DoLah::Calendar calendar;
	};

	class SearchTaskCommand : public ITaskCommand {
	public:
		SearchTaskCommand();
		~SearchTaskCommand();

		std::string getQuery();
		DoLah::Calendar getCalendar();

		void setQuery(std::string);
		void setCalendar(DoLah::Calendar cal);

		void execute();

	private:
		std::string query;
		DoLah::Calendar calendar;
	};

	class UndoTaskCommand : public ITaskCommand {
	public:
		UndoTaskCommand();
		~UndoTaskCommand();

		void execute();
	
	private:
		DoLah::Calendar calendar;
	};

	class RedoTaskCommand : public ITaskCommand {
	public:
		RedoTaskCommand();
		~RedoTaskCommand();

		void execute();

	private:
		DoLah::Calendar calendar;
	};

}
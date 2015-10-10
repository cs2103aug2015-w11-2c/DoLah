#pragma once

#include <vector>
#include <string>
#include <Models/Task.h>
#include <Models/Calendar.h>

namespace DoLah {

	class ITaskCommand {
	public:
		virtual ~ITaskCommand();

		virtual void execute();
	};

	class AddTaskCommand : public ITaskCommand {
	public:
		AddTaskCommand();
		AddTaskCommand(DoLah::AbstractTask*);
		~AddTaskCommand();

		AbstractTask * getTask();

		void setCalendar(DoLah::Calendar*);

		void execute();

	private:
		DoLah::AbstractTask* task;
		DoLah::Calendar* calendar;
	};

	class EditTaskCommand : public ITaskCommand {
	public:
		EditTaskCommand();
		EditTaskCommand(int, DoLah::AbstractTask *);
		~EditTaskCommand();

		void setCalendar(DoLah::Calendar*);

		void execute();

	private:
		int taskIndex;
		DoLah::AbstractTask* task;
		DoLah::Calendar * calendar;
	};

	class DeleteTaskCommand : public ITaskCommand {
	public:
		DeleteTaskCommand();
		DeleteTaskCommand(int);
		~DeleteTaskCommand();

		void setCalendar(DoLah::Calendar);

		void execute();

	private:
		int taskIndex;
		DoLah::Calendar calendar;
	};

	class ClearTaskCommand : public ITaskCommand {
	public:
		ClearTaskCommand();
		~ClearTaskCommand();

		void setCalendar(DoLah::Calendar*);

		void execute();

	private:
		DoLah::Calendar* calendar;
	};

	class SearchTaskCommand : public ITaskCommand {
	public:
		SearchTaskCommand();
		SearchTaskCommand(std::string);
		~SearchTaskCommand();

		void setCalendar(DoLah::Calendar);

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
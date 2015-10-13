#pragma once

#include <vector>
#include <string>
#include "Models/Task.h"
#include "Models/Calendar.h"

namespace DoLah {

	class ITaskCommand {
	public:
		virtual ~ITaskCommand() = 0;
        void setCalendar(DoLah::Calendar&);
		virtual void execute() = 0;

    private:
        Calendar& calendar = Calendar::getInstance();
	};

	class AddTaskCommand : public ITaskCommand {
	public:
		AddTaskCommand();
		AddTaskCommand(DoLah::AbstractTask*);
		~AddTaskCommand();

		void execute();

	private:
		DoLah::AbstractTask* task;
        Calendar& calendar = Calendar::getInstance();
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
        Calendar& calendar = Calendar::getInstance();
    };

	class DeleteTaskCommand : public ITaskCommand {
	public:
		DeleteTaskCommand();
		DeleteTaskCommand(int);
		~DeleteTaskCommand();

		void execute();

	private:
		int taskIndex;
        Calendar& calendar = Calendar::getInstance();
    };

	class ClearTaskCommand : public ITaskCommand {
	public:
		ClearTaskCommand();
		~ClearTaskCommand();

		void execute();

	private:
        Calendar& calendar = Calendar::getInstance();
    };

	class SearchTaskCommand : public ITaskCommand {
	public:
		SearchTaskCommand();
		SearchTaskCommand(std::string);
		~SearchTaskCommand();

		void execute();

	private:
		std::string query;
        Calendar& calendar = Calendar::getInstance();
    };

	class UndoTaskCommand : public ITaskCommand {
	public:
		UndoTaskCommand();
		~UndoTaskCommand();

		void execute();
	
	private:
        Calendar& calendar = Calendar::getInstance();
    };

	class RedoTaskCommand : public ITaskCommand {
	public:
		RedoTaskCommand();
		~RedoTaskCommand();

		void execute();

	private:
        Calendar& calendar = Calendar::getInstance();
    };

}
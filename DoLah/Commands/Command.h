#pragma once

#include <vector>
#include <string>
#include "Models/Task.h"
#include "Models/Calendar.h"

namespace DoLah {

	class AbstractCommand {
	public:
		virtual ~AbstractCommand() = 0;
        void setCalendar(DoLah::Calendar*);
		virtual void execute() = 0;

    protected:
        DoLah::Calendar* calendar;
	};

	class AddTaskCommand : public AbstractCommand {
	public:
		AddTaskCommand();
		AddTaskCommand(DoLah::AbstractTask*);
		~AddTaskCommand();

		void execute();

	private:
		DoLah::AbstractTask* task;
	};

	class EditTaskCommand : public AbstractCommand {
	public:
		EditTaskCommand();
		EditTaskCommand(int, DoLah::AbstractTask *);
		~EditTaskCommand();
		void execute();

	private:
		int taskIndex;
		DoLah::AbstractTask* task;
	};

    class SetDoneTaskCommand : public AbstractCommand {
    public:
        SetDoneTaskCommand(int);
        ~SetDoneTaskCommand();
        void execute();
    private:
        int taskIndex;
    };

	class DeleteTaskCommand : public AbstractCommand {
	public:
		DeleteTaskCommand();
		DeleteTaskCommand(int);
		~DeleteTaskCommand();

		void execute();

	private:
		int taskIndex;
	};

	class ClearTaskCommand : public AbstractCommand {
	public:
		ClearTaskCommand();
		~ClearTaskCommand();

		void execute();
	};

	class SearchTaskCommand : public AbstractCommand {
	public:
		SearchTaskCommand();
        SearchTaskCommand(std::string);
		SearchTaskCommand(std::string, std::vector<AbstractTask*> *);
		~SearchTaskCommand();

		void execute();

	private:
		std::string query;
        std::vector<AbstractTask*> ** resultVector;
	};

	class UndoTaskCommand : public AbstractCommand {
	public:
		UndoTaskCommand();
		~UndoTaskCommand();

		void execute();
	};

	class RedoTaskCommand : public AbstractCommand {
	public:
		RedoTaskCommand();
		~RedoTaskCommand();

		void execute();
	};

}
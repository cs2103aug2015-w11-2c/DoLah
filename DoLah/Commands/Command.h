#pragma once

#include <vector>
#include <string>
#include "Models/Task.h"
#include "Models/Calendar.h"
#include "Models/CommandHistory.h"
#include "Models/CalendarInverter.h"

namespace DoLah {

	class AbstractCommand {
	public:
		virtual ~AbstractCommand() = 0;
        void setCalendar(DoLah::Calendar*);
		virtual void execute() = 0;
        virtual void revert() = 0;

    protected:
        DoLah::Calendar* calendar;
	};

	class AddTaskCommand : public AbstractCommand {
	public:
		AddTaskCommand();
		AddTaskCommand(DoLah::AbstractTask*);
		~AddTaskCommand();

		void execute();
        void revert();

	private:
		DoLah::AbstractTask* task;
	};

	class EditTaskCommand : public AbstractCommand {
	public:
		EditTaskCommand();
		EditTaskCommand(int, DoLah::AbstractTask *);
		~EditTaskCommand();
		
        void execute();
        void revert();

	private:
		int taskIndex;
		DoLah::AbstractTask* task;
        DoLah::AbstractTask* oldTask;
	};

    class SetDoneTaskCommand : public AbstractCommand {
    public:
        SetDoneTaskCommand(int);
        ~SetDoneTaskCommand();
        
        void execute();
        void revert();
    
    private:
        int taskIndex;
        DoLah::AbstractTask* oldTask;
    };

	class DeleteTaskCommand : public AbstractCommand {
	public:
		DeleteTaskCommand();
		DeleteTaskCommand(int);
		~DeleteTaskCommand();

		void execute();
        void revert();

	private:
		int taskIndex;
        DoLah::AbstractTask* oldTask;
	};

	class ClearTaskCommand : public AbstractCommand {
	public:
		ClearTaskCommand();
		~ClearTaskCommand();

		void execute();
        void revert();

    private:
        std::vector<AbstractTask*> oldTaskList;
        std::vector<AbstractTask*> oldDoneList;
	};

	class SearchTaskCommand : public AbstractCommand {
	public:
		SearchTaskCommand();
        SearchTaskCommand(std::string);
		SearchTaskCommand(std::string, std::vector<AbstractTask*> *);
		~SearchTaskCommand();

		void execute();
        void revert();

	private:
		std::string query;
        std::vector<AbstractTask*> ** resultVector;
	};

	class UndoTaskCommand : public AbstractCommand {
	public:
		UndoTaskCommand();
		~UndoTaskCommand();

		void execute();
        void revert(); // DO NOT CALL
    private:
        static std::string ILLEGAL_FUNCTION_CALL_MESSAGE;
	};

	class RedoTaskCommand : public AbstractCommand {
	public:
		RedoTaskCommand();
		~RedoTaskCommand();

		void execute();
        void revert(); // DO NOT CALL
    private:
        static std::string ILLEGAL_FUNCTION_CALL_MESSAGE;
	};

}
#pragma once

#include <vector>
#include <string>
#include "Models/Task.h"
#include "Models/Calendar.h"
#include "Models/CommandHistory.h"
#include "Models/CalendarInverter.h"

namespace DoLah {
    /**
     * @class AbstractCommand Command.h Commands/Command.h
     * @brief The abstract class that all Commands are based off of. 
     * You should treat this more like an interface than an actual class.
     *
     * You should not be instantiating an instance of this class.
     * Attempting to call execute() or revert() without a Calendar set will likely cause the 
     * program to crash.
     * All commands save enough state in order to revert the changes that they make in the Calendar.
     * Commands that do not have a valid revert() operation should be included in CommandInvoker
     * for exclusion.
     */
    class AbstractCommand {
    public:
        virtual ~AbstractCommand() = 0;
        
        /**
         * @brief Associates a Calendar with this Command instance to act on.
         *
         * It should be noted that only child classes should be calling this function.
         * @param calendar A pointer to the Calendar.
         */
        void setCalendar(DoLah::Calendar*);

        /**
         * @brief When called, will call functions from the associated Calendar to carry out
         * stipulated operation. This command must be implemented.
         *
         * RedoTaskCommand also calls this function.
         */
        virtual void execute() = 0;

        /**
         * @brief When called, will call functions from the CalendarInverter and CommandHistory 
         * classes to reverse the stipulated operation. This function must be implemented unless 
         * it is not to be included in CommandHistory. This function should not directly call 
         * functions that mutate the Calendar, but instead go through the CalendarInverter class.
         *
         * Generally this will only be called by UndoTaskCommand.
         */
        virtual void revert() = 0;

    protected:
        DoLah::Calendar* calendar; ///< Pointer to the Calendar to be acted on.
    };

    /**
     * @class AddTaskCommand Command.h Commands/Command.h
     * @brief The command class that encapsulates the action of adding a task to the Calendar.
     */
    class AddTaskCommand : public AbstractCommand {
    public:
        /**
         * @brief Instantiates an instance of AddTaskCommand with the task to be added attached.
         *
         * @param newTask The task to be added.
         */
        AddTaskCommand(DoLah::AbstractTask*);
        ~AddTaskCommand();

        /**
         * @brief When called, will call functions from the associated Calendar to add the task
         * to the Calendar.
         */
        void execute();

        /**
         * @brief When called, will call functions from CalendarInverter and CommandHistory 
         * to reverse the operation of adding the task to the Calendar.
         */
        void revert();

    private:
        DoLah::AbstractTask* task; ///< The task to be added.
    };

    /**
     * @class EditTaskCommand Command.h Commands/Command.h
     * @brief The command class that encapsulates the action of editing a task in the Calendar.
     */
    class EditTaskCommand : public AbstractCommand {
    public:
        /**
         * @brief Instantiates an instance of EditTaskCommand with the index of the task to be 
         * edited and the task for it to be replaced with attached.
         *
         * @param taskIndex The index of the task to be replaced.
         * @param targetTask The task with the new details.
         */
        EditTaskCommand(int, DoLah::AbstractTask *);
        ~EditTaskCommand();
        
        /**
         * @brief When called, will call functions from the associated Calendar to edit the task
         * in the Calendar.
         */
        void execute();

        /**
         * @brief When called, will call functions from CalendarInverter and CommandHistory 
         * to reverse the operation of editing the task in the Calendar.
         */
        void revert();

    private:
        int taskIndex; ///< The index of the task to be replaced in the Calendar
        DoLah::AbstractTask* task; ///< The task with the new details.
        DoLah::AbstractTask* oldTask; ///< The task replaced in the execute() call.
    };

    /**
     * @class SetDoneTaskCommand Command.h Commands/Command.h
     * @brief The command class that encapsulates the action of marking a task as done in the 
     * Calendar.
     */
    class SetDoneTaskCommand : public AbstractCommand {
    public:
        /**
         * @brief Instantiates an instance of SetDoneTaskComamand with the index of the task to be marked
         * as done attached.
         *
         * @param taskIndex The index of the task to be marked as done.
         */
        SetDoneTaskCommand(int);
        ~SetDoneTaskCommand();
        
        /**
         * @brief When called, will call functions from the associated Calendar to mark the task
         * as done in the Calendar.
         */
        void execute();

        /**
         * @brief When called, will call functions from CalendarInverter and CommandHistory 
         * to reverse the operation of marking the task as done in the Calendar.
         */
        void revert();
    
    private:
        int taskIndex; ///< The index of the task to be marked as done.
        DoLah::AbstractTask* oldTask; ///< The task that was marked as done during execute().
    };

    /**
     * @class SetUndoneTaskCommand Command.h Commands/Command.h
     * @brief The command class that encapsulates the action of marking a task as undone in the 
     * Calendar.
     */
    class SetUndoneTaskCommand : public AbstractCommand {
    public:
        /**
         * @brief Instantiates an instance of SetUndoneTaskComamand with the index of the task to be marked
         * as not done attached.
         *
         * @param taskIndex The index of the task to be marked as not done.
         */
        SetUndoneTaskCommand(int);
        ~SetUndoneTaskCommand();

        /**
         * @brief When called, will call functions from the associated Calendar to mark the task
         * as not done in the Calendar.
         */
        void execute();

        /**
         * @brief When called, will call functions from CalendarInverter and CommandHistory 
         * to reverse the operation of marking the task as not done in the Calendar.
         */
        void revert();
    private:
        int taskIndex; ///< The index of the task to be marked as not done.
        DoLah::AbstractTask* oldTask; ///< The task that was marked as not done on the execute() call.
    };

    /**
     * @class DeleteTaskCommand Command.h Commands/Command.h
     * @brief The Command class that encapsulates the action of deleting a task in the Calendar.
     */
    class DeleteTaskCommand : public AbstractCommand {
    public:
        /**
         * @brief Instantiates an instance of DeleteTaskComamand with the index of the task to be 
         * deleted attached.
         *
         * @param taskIndex The index of the task to be deleted.
         */
        DeleteTaskCommand(int);
        ~DeleteTaskCommand();

        /**
         * @brief When called, will call functions from the associated Calendar to delete the task
         * in the Calendar.
         */
        void execute();

        /**
         * @brief When called, will call functions from CalendarInverter and CommandHistory 
         * to reverse the operation of deleting the task in the Calendar.
         */
        void revert();

    private:
        int taskIndex; ///< The index of the task to be deleted.
        DoLah::AbstractTask* oldTask; ///< The task that was deleted on the execute() call.
    };

    /**
     * @class ClearTaskCommand Command.h Commands/Command.h
     * @brief The Command class that encapsulates the action of clearing all tasks from the 
     * Calendar.
     */
    class ClearTaskCommand : public AbstractCommand {
    public:
        ClearTaskCommand();
        ~ClearTaskCommand();

        /**
         * @brief When called, will call functions from the associated Calendar to clear all tasks
         * from the Calendar.
         */
        void execute();

        /**
         * @brief When called, will call functions from CalendarInverter and CommandHistory 
         * to reverse the operation of clearing all tasks in the Calendar.
         */
        void revert();

    private:
        std::vector<AbstractTask*> oldTaskList; ///< The copy of taskList wiped on execute().
        std::vector<AbstractTask*> oldDoneList; ///< The copy of doneList wiped on execute().
    };

    /**
     * @class SearchTaskCommand Command.h Commands/Command.h
     * @brief The Command class that encapsulates the action of searching for tasks containing the
     * search string in their name field from the Calendar.
     */
    class SearchTaskCommand : public AbstractCommand {
    public:
        /**
         * Instantiates an instance of SearchTaskComamand with the search string attached.
         *
         * @param query The search string.
         */
        SearchTaskCommand(std::string);
        ~SearchTaskCommand();

        /**
         * @brief When called, will call functions from the associated Calendar to search for
         * tasks with name fields containing the search string.
         */
        void execute();

        /**
         * @brief Not actually implemented and the Command is thus excluded from inclusion in
         * CommandHistory. Do not call this command.
         */
        void revert();

    private:
        std::string query; ///< The search string to look for in the name of the tasks.
    };

    /**
     * @class SearchDateTaskCommand Command.h Commands/Command.h
     * @brief The Command class that encapsulates the action of searching for tasks falling 
     * between the given date range from the Calendar.
     */
    class SearchDateTaskCommand : public AbstractCommand {
    public:
        /**
         * Instantiates an instance of SearchTaskComamand with the given date range.
         *
         * @param from The start date and time of the search.
         * @param to The end date and time of the search.
         */
        SearchDateTaskCommand(std::tm, std::tm);
        ~SearchDateTaskCommand();

        /**
         * @brief When called, will call functions from the associated Calendar to search for
         * tasks with name fields containing the search string.
         */
        void execute();

        /**
         * @brief Not actually implemented and the Command is thus excluded from inclusion in
         * CommandHistory. Do not call this command.
         */
        void revert();

    private:
        std::tm from; ///< The start date and time of the search.
        std::tm to; ///< The end date and time of the search.
    };

    /**
     * @class UndoTaskCommand Command.h Commands/Command.h
     * @brief The Command class that encapsulates the action of undoing the last executed Command.
     */
    class UndoTaskCommand : public AbstractCommand {
    public:
        UndoTaskCommand();
        ~UndoTaskCommand();

        /**
         * @brief When called, will call functions from CommandHistory and CalendarInverter
         * in order to undo the last Command.
         */
        void execute();

        /**
         * @brief Not actually implemented and the Command is thus excluded from inclusion in
         * CommandHistory. Do not call this command.
         */
        void revert();
    private:
        static std::string ILLEGAL_FUNCTION_CALL_MESSAGE; ///< Thrown when revert is called.
    };

    /**
     * @class RedoTaskCommand Command.h Commands/Command.h
     * @brief The Command class that encapsulates the action of redoing the last undone Command.
     */
    class RedoTaskCommand : public AbstractCommand {
    public:
        RedoTaskCommand();
        ~RedoTaskCommand();

        /**
         * @brief When called, will call functions from the associated Calendar and 
         * CalendarInverter in order to redo the last undone Command.
         */
        void execute();

        /**
         * @brief Not actually implemented and the Command is thus excluded from inclusion in
         * CommandHistory. Do not call this command.
         */
        void revert();
    private:
        static std::string ILLEGAL_FUNCTION_CALL_MESSAGE; ///< Thrown when revert is called.
    };

}
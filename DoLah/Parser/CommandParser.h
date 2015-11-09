
#pragma once

#include <string>
#include <vector>
#include <chrono>
#include "assert.h"

#include "ParserLibrary.h"
#include "TaskParser.h"

#include "Commands/Command.h"
#include "Models/Task.h"


namespace DoLah {
    /**
    * @class CommandParser CommandParser.h Parser/CommandParser.h
    * @brief Receives a string and returns a Command object.
    *
    * If the input is invalid, it will throw invalid_argument exception.
    */

    class CommandParser {

    public:
        CommandParser();
        ~CommandParser();

        /**
         * Parse input string into a Command object.
         * @param[in]       input String to be parsed.
         * @return Command object.
         */
        static AbstractCommand* parse(std::string);

        /**
         * Parse input string vector into a AddTaskCommand.
         * @param[in]       inputArr String vector to be parsed.
         * @return AddTaskCommand object.
         */
        static AddTaskCommand parseAdd(std::vector<std::string>);

        /**
         * Parse input string vector into a SearchTaskCommand.
         * @param[in]       inputArr String vector to be parsed.
         * @return SearchTaskCommand object.
         */
        static SearchTaskCommand parseSearch(std::vector<std::string>);

        /**
         * Parse input string vector into a SetDoneTaskCommand.
         * @param[in]       inputArr String vector to be parsed.
         * @return SetDoneTaskCommand object.
         */
        static SetDoneTaskCommand parseSetDone(std::vector<std::string>);

        /**
         * Parse input string vector into a SetUndoneTaskCommand.
         * @param[in]       inputArr String vector to be parsed.
         * @return SetUndoneTaskCommand object.
         */
        static SetUndoneTaskCommand parseSetUndone(std::vector<std::string>);

        /**
         * Parse input string vector into a EditTaskCommand.
         * @param[in]       inputArr String vector to be parsed.
         * @return EditTaskCommand object.
         */
        static EditTaskCommand parseEdit(std::vector<std::string>);
        
        /**
         * Parse input string vector into a DeleteTaskCommand.
         * @param[in]       inputArr String vector to be parsed.
         * @return DeleteTaskCommand object.
         */
        static DeleteTaskCommand parseDelete(std::vector<std::string>);
        
        /**
         * Parse input string vector into a ClearTaskCommand.
         * @param[in]       inputArr String vector to be parsed.
         * @return ClearTaskCommand object.
         */
        static ClearTaskCommand parseClear(std::vector<std::string>);
        
        /**
         * Parse input string vector into a UndoTaskCommand.
         * @param[in]       inputArr String vector to be parsed.
         * @return UndoTaskCommand object.
         */
        static UndoTaskCommand parseUndo(std::vector<std::string>);
        
        /**
         * Parse input string vector into a RedoTaskCommand.
         * @param[in]       inputArr String vector to be parsed.
         * @return RedoTaskCommand object.
         */
        static RedoTaskCommand parseRedo(std::vector<std::string>);

        /**
         * Prune the command from the string vector.
         * Currently the format is fixed, and thus always the first element is pruned.
         * @param[in]       inputArr String vector to be pruned
         * @return Pruned string vector.
         */
        // Fixed format ~ command is always at the front
        static std::vector<std::string> pruneCommand(std::vector<std::string> lineArr);
    private:
        /// @brief List of strings that indicates the string is an AddTaskCommand
        static std::vector<std::string> ADD;
        /// List of strings that indicates the string is a SearchTaskCommand
        static std::vector<std::string> SEARCH;
        /// List of strings that indicates the string is a DoneTaskCommand
        static std::vector<std::string> DONE;
        /// List of strings that indicates the string is an UndoneTaskCommand
        static std::vector<std::string> UNDONE;
        /// List of strings that indicates the string is an EditTaskCommand
        static std::vector<std::string> EDIT;
        /// List of strings that indicates the string is a DeleteTaskCommand
        static std::vector<std::string> DELETE;
        /// List of strings that indicates the string is a ClearTaskCommand
        static std::vector<std::string> CLEAR;
        /// List of strings that indicates the string is an UndoTaskCommand
        static std::vector<std::string> UNDO;
        /// List of strings that indicates the string is a RedohTaskCommand
        static std::vector<std::string> REDO;

        /// Message to be thrown when too many arguments are given for the command type.
        static std::string TOO_MANY_ARGUMENTS_MESSAGE;
        /// Message to be thrown when too little arguments are given for the command type.
        static std::string TOO_LITTLE_ARGUMENTS_MESSAGE;
        /// Message to be thrown when the task ID for edit or delete is nonsensual.
        static std::string INVALID_TASK_ID_ARGUMENT;
    };
}
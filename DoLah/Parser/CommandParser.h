#pragma once

#include <string>
#include <vector>
#include <chrono>
#include "assert.h"

#include "ParserLibrary.h"
#include "CommandTokenizer.h"
#include "TaskParser.h"

#include "Commands/Command.h"
#include "Models/Task.h"


namespace DoLah {
    class CommandParser {

    public:
        CommandParser();
        ~CommandParser();

        static AbstractCommand* parse(std::string);
        static AddTaskCommand parseAdd(std::vector<std::string>);
        static SearchTaskCommand parseSearch(std::vector<std::string>);
        static SetDoneTaskCommand parseSetDone(std::vector<std::string>);
        static EditTaskCommand parseEdit(std::vector<std::string>);
        static DeleteTaskCommand parseDelete(std::vector<std::string>);
        static ClearTaskCommand parseClear(std::vector<std::string>);
        static UndoTaskCommand parseUndo(std::vector<std::string>);
        static RedoTaskCommand parseRedo(std::vector<std::string>);
    private:
        static std::vector<std::string> ADD;
        static std::vector<std::string> SEARCH;
        static std::vector<std::string> DONE;
        static std::vector<std::string> EDIT;
        static std::vector<std::string> DELETE;
        static std::vector<std::string> CLEAR;
        static std::vector<std::string> UNDO;
        static std::vector<std::string> REDO;
        static std::string UNHANDLED_COMMAND_MESSAGE;
        static std::string UNKNOWN_COMMAND_MESSAGE;
        static std::string TOO_MANY_ARGUMENTS_MESSAGE;
        static std::string TOO_LITTLE_ARGUMENTS_MESSAGE;
        static std::string INVALID_TASK_ID_ARGUMENT;
    };
}
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

        static ITaskCommand* parse(std::string);
        static AddTaskCommand parseAdd(std::vector<std::string>);
        static SearchTaskCommand parseSearch(std::vector<std::string>);
        static EditTaskCommand parseEdit(std::vector<std::string>);
        static DeleteTaskCommand parseDelete(std::vector<std::string>);
        static ClearTaskCommand parseClear(std::vector<std::string>);
        static UndoTaskCommand parseUndo(std::vector<std::string>);
    private:
        static std::string ADD;
        static std::string SEARCH;
        static std::string EDIT;
        static std::string DELETE;
        static std::string CLEAR;
        static std::string UNDO;

        static std::string UNHANDLED_COMMAND_MESSAGE;
        static std::string UNKNOWN_COMMAND_MESSAGE;
        static std::string TOO_MANY_ARGUMENTS_MESSAGE;
        static std::string TOO_LITTLE_ARGUMENTS_MESSAGE;
        static std::string INVALID_TASK_ID_ARGUMENT;
    };
}
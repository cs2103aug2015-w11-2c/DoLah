#pragma once

#include <string>
#include <vector>
#include <chrono>

#include "ParserLibrary.h"
#include "CommandTokenizer.h"

#include "Commands/Command.h"
#include "Models/Task.h"


namespace DoLah {
    class CommandParser {

    public:
        CommandParser();
        ~CommandParser();

        // needs to use Calendar parameter later
        static ITaskCommand* parse(std::string);
        static AddTaskCommand parseAdd(std::vector<std::string>);
        static SearchTaskCommand parseSearch(std::vector<std::string>);
        static EditTaskCommand parseEdit(std::vector<std::string>);
        static DeleteTaskCommand parseDelete(std::vector<std::string>);
        static ClearTaskCommand parseClear();
        static UndoTaskCommand parseUndo();
        static AbstractTask* parseTask(std::vector<std::string>);
    private:
        static std::string ADD;
        static std::string SEARCH;
        static std::string EDIT;
        static std::string DELETE;
        static std::string CLEAR;
        static std::string UNDO;

        static std::string UNKNOWN_COMMAND_MESSAGE;
        static std::string TOO_MANY_ARGUMENTS_MESSAGE;
        static std::string TOO_LITTLE_ARGUMENTS_MESSAGE;
    };
}
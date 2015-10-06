#pragma once

#include <string>
#include <vector>
#include <chrono>

#include "ParserLibrary.h"
#include "CommandTokenizer.h"

#include "Commands/Command.h"
#include "Models/Task.h"

#include "Models/Calendar.h"


namespace DoLah {
    class CommandParser {

    public:
        CommandParser();
        ~CommandParser();

        // needs to use Calendar parameter later
        static void parse(std::string);
        static AddTaskCommand parseAdd(std::vector<std::string>);
        static void parseSearch(std::string);
        static void parseEdit(std::vector<std::string>);
        static void parseDelete(std::vector<std::string>);
        static void parseClear();
        static void parseUndo();
    private:
        static std::string ADD;
        static std::string SEARCH;
        static std::string EDIT;
        static std::string DELETE;
        static std::string CLEAR;
        static std::string UNDO;

        static std::string TOO_MANY_ARGUMENTS_MESSAGE;
        static std::string TOO_LITTLE_ARGUMENTS_MESSAGE;
    };
}
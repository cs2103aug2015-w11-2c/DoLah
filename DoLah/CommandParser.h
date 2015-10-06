#pragma once

#include <string>
#include <vector>
#include <chrono>

#include "ParserLibrary.h"
#include "CommandTokenizer.h"
#include "Models/Task.h"
#include "Commands/Command.h"


namespace DoLah {
    class CommandParser {

    public:
        CommandParser();
        ~CommandParser();

        // needs to use Calendar parameter later
        void parse(std::string);
        void parseAdd(std::vector<std::string>);
        void parseSearch(std::string);
        void parseEdit(std::vector<std::string>);
        void parseDelete(std::vector<std::string>);
        void parseClear();
        void parseUndo();
    private:
        CommandTokenizer tokenizer;

        std::string ADD = "add";
        std::string SEARCH = "search";
        std::string EDIT = "edit";
        std::string DELETE = "delete";
        std::string CLEAR = "clear";
        std::string UNDO = "undo";

        std::string TOO_MANY_ARGUMENTS_MESSAGE = "Too many arguments";
        std::string TOO_LITTLE_ARGUMENTS_MESSAGE = "Too little arguments";
    };
}
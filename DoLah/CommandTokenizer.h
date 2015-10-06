#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <regex>
#include <iterator>

#include "ParserLibrary.h"
#include "DateTimeParser.h"

namespace DoLah {

    class CommandTokenizer {
    public:
        CommandTokenizer();
        ~CommandTokenizer();

        std::string findCommand(std::vector<std::string>);

        std::string findDescription(std::vector<std::string>);
        std::vector<std::string> findTags(std::vector<std::string>);
        std::vector<std::tm> findDate(std::vector<std::string>);
        int findTaskID(std::vector<std::string>);

    private:
        std::vector<std::string> commandList = { "add", "display", "undo", "delete", "edit", "clear", "search", "sort" };
        std::vector<std::string> timeSubCommandList = { "on" };

        std::string tag = "#";

        std::string UNKNOWN_COMMAND_MESSAGE = "command not recognized";
    };

}
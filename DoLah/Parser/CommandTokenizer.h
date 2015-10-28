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

        // Fixed format ~ command is always at the front
        static std::string findCommand(std::vector<std::string>&);
        // Prune the comand part from the input
        static std::vector<std::string> pruneCommand(std::vector<std::string>);
    private:
        static std::vector<std::string> commandList;
    };
}
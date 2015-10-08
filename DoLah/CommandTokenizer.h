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
        // It will prune the comand part from the input
        static std::string findCommand(std::vector<std::string>&);

        // Fixed format ~ date is at the end of command indicated by subcommand 'on'.
        // It will prune the date part from the input
        static std::vector<std::tm> findDate(std::vector<std::string>&);

        // The input should not have date already, and thus findDate always come before this.
        // Tag is ignored and the hashes remain in description.
        static std::string findDescription(std::vector<std::string>);
        
        // A tag is indicated by hash (#)
        static std::vector<std::string> findTags(std::vector<std::string>);

    private:
        static std::vector<std::string> commandList;
        static std::vector<std::string> timeSubCommandList;

        static std::string tag;
    };
}
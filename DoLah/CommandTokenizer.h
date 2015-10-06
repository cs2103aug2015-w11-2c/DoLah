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

        // Fixed format ~ command is always on the front
        static std::string findCommand(std::vector<std::string>);
        
        // The input should not have date already, and thus findDate always come before this.
        // Tag is ignored as further consideration is needed.
        static std::string findDescription(std::vector<std::string>);
        
        // Tag is indicated by hash (#)
        static std::vector<std::string> findTags(std::vector<std::string>);

        // Fixed format ~ date is at the end of command indicated by subcommand 'on'.
        static std::vector<std::tm> findDate(std::vector<std::string>);

    private:
        static std::vector<std::string> commandList;
        static std::vector<std::string> timeSubCommandList;

        static std::string tag;
    };
}
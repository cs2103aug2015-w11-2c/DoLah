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

        static std::string findCommand(std::vector<std::string>);

        static std::string findDescription(std::vector<std::string>);
        static std::vector<std::string> findTags(std::vector<std::string>);
        static std::vector<std::tm> findDate(std::vector<std::string>);
        static int findTaskID(std::vector<std::string>);

    private:
        static std::vector<std::string> commandList;
        static std::vector<std::string> timeSubCommandList;

        static std::string tag;
    };
}
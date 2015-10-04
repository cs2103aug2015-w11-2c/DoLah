#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <chrono>

#include "ParserLibrary.h"

class CommandTokenizer {
public:
    CommandTokenizer();
    ~CommandTokenizer();

    std::string findCommand(std::vector<std::string> lineArr);

    std::string findDescription(std::vector<std::string> lineArr);
    std::vector<std::string> findTags(std::vector<std::string> lineArr);
    std::vector<std::chrono::system_clock::time_point> findDate(std::vector<std::string> lineArr);


private:
    std::vector<std::string> commandList = { "add", "display", "undo", "delete", "edit", "clear", "search", "sort" };
    std::vector<std::string> timeSubCommandList = { "on" };

    std::string tag = "#";

    std::string UNKNOWN_COMMAND_MESSAGE = "command not recognized";
};


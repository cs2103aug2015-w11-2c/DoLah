#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <chrono>

#include "TokenizerLibrary.h"

class CommandTokenizer {
public:
    CommandTokenizer();
    ~CommandTokenizer();

    std::vector<std::string> findCommand(std::vector<std::string> lineArr);
    std::vector<std::string> findTags(std::vector<std::string> lineArr);
    std::vector<std::chrono::system_clock::time_point> findDate(std::vector<std::string> lineArr);
    std::vector<std::string> findDescription(std::vector<std::string> lineArr);
    std::vector<int> findPriority(std::vector<std::string> lineArr);


private:
    std::vector<std::string> commandList = { "add", "display", "undo", "delete", "edit", "clear", "search", "sort" };
    std::vector<std::string> addSubCommandList = { "on" };

    std::string tag = "#";

};


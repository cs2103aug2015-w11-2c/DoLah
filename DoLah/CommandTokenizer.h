#pragma once

#include <string>
#include <vector>

#include "TokenizerLibrary.h""

class CommandTokenizer {
public:
    CommandTokenizer();
    ~CommandTokenizer();

    std::vector<std::string> tokenize(std::string line);

private:
    std::vector<std::string> commandList = { "add", "display", "undo", "delete", "edit", "clear", "search", "sort"};
    std::vector<std::string> addSubCommandList = { "on" };
    
    std::string findCommand(std::vector<std::string> lineArr);
    std::vector<std::string> findTags(std::string line);
    std::vector<std::string> findDate(std::string line);
    std::vector<std::string> findDescription(std::string line);
};


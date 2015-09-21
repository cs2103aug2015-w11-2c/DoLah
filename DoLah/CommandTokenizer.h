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
    std::vector<std::string> commandList = { "add", "dislay", "undo", "delete", "edit", "clear", "search", "sort"};
};


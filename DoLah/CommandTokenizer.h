#pragma once

#include <string>
#include <vector>

#include "TokenizerLibrary.h"
#include "ITokenObject.h"

class CommandTokenizer {
public:
    CommandTokenizer();
    ~CommandTokenizer();

    std::vector<ITokenObject *> tokenize(std::string line);

    StringToken* findCommand(std::vector<std::string> lineArr);

    std::vector<ITokenObject *> tokenizeAdd(std::vector<std::string> lineArr);
    StringToken* findTags(std::vector<std::string> lineArr);
    DateTimeToken* findDate(std::vector<std::string> lineArr);
    StringToken* findDescription(std::vector<std::string> lineArr);
    IntegerToken* findPriority(std::vector<std::string> lineArr);


private:
    std::vector<std::string> commandList = { "add", "display", "undo", "delete", "edit", "clear", "search", "sort"};
    std::vector<std::string> addSubCommandList = { "on" };

    std::string tag = "#";
    
};


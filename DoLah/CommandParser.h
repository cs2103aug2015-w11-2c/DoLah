#pragma once

#include <string>
#include <vector>

#include "ParserLibrary.h"
#include "CommandTokenizer.h"

class CommandParser {
public:
    CommandParser();
    ~CommandParser();

    void parse(std::string);
    void parseAdd(std::vector<std::string>);
private:
    CommandTokenizer tokenizer;
    std::string ADD = "add";
    std::string EDIT = "edit";
    std::string SEARCH = "search";
    std::string CLEAR = "clear";
    std::string DELETE = "delete";
    std::string UNDO = "undo";
};


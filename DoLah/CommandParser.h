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
    std::string parseSearch(std::string);
private:
    CommandTokenizer tokenizer;
    
    std::string ADD = "add";
    std::string EDIT = "edit";
    std::string SEARCH = "search";
    std::string CLEAR = "clear";
    std::string DELETE = "delete";
    std::string UNDO = "undo";

    std::string TOO_MANY_ARGUMENTS_MESSAGE = "Too many arguments";
    std::string TOO_LITTLE_ARGUMENTS_MESSAGE = "Too little arguments";
};


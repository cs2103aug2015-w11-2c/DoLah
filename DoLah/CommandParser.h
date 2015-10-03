#pragma once

#include <string>
#include <vector>

#include "ParserLibrary.h"
#include "CommandTokenizer.h"

class CommandParser {
public:
    CommandParser();
    ~CommandParser();

    void parse(const std::string &);

};


#include "CommandParser.h"



CommandParser::CommandParser() {
}


CommandParser::~CommandParser() {
}


void CommandParser::parseAdd(std::vector<std::string> inputArr) {
    tokenizer.findDescription(inputArr);
    tokenizer.findTags(inputArr);
    tokenizer.findPriority(inputArr);
}


void CommandParser::parse(std::string input) {
    std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");
    std::string command = tokenizer.findCommand(inputArr);
    if (command == ADD) {
        parseAdd(inputArr);
    } else if (command == EDIT) {
    } else if (command == SEARCH) {
    } else if (command == CLEAR) {
    } else if (command == DELETE) {
    } else if (command == UNDO) {
    }
}


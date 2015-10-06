#include "CommandParser.h"



CommandParser::CommandParser() {
}


CommandParser::~CommandParser() {
}


void CommandParser::parseAdd(std::vector<std::string> inputArr) {
    std::string description = tokenizer.findDescription(inputArr);
    std::vector<std::string> tags = tokenizer.findTags(inputArr);
    std::vector<std::tm> dueDate = tokenizer.findDate(inputArr);

    //make ITaskCommand
}


void CommandParser::parseSearch(std::string input) {
    int pos = input.find(" ");
    std::string arg = input.substr(pos, input.size() - pos);

    //make ITaskCommand
}


void CommandParser::parseEdit(std::vector<std::string> inputArr) {
    int arg = std::stoi(inputArr.at(1));
    /*int id = tokenizer.findTaskID(inputArr);*/
    std::string description = tokenizer.findDescription(inputArr);
    std::vector<std::string> tags = tokenizer.findTags(inputArr);
    std::vector<std::tm> dueDate = tokenizer.findDate(inputArr);

    //make ITaskCommand
}


void CommandParser::parseDelete(std::vector<std::string> inputArr) {
    int arg = std::stoi(inputArr.at(1));

    //make ITaskCommand
}


void CommandParser::parseClear() {
    //make ITaskCommand
}


void CommandParser::parseUndo() {
    //make ITaskCommand
}


void CommandParser::parse(std::string input) {
    std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");
    std::string command = tokenizer.findCommand(inputArr);
    if (command == ADD) {
        if (inputArr.size() == 1) {
            throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
        }
        parseAdd(inputArr);
    } else if (command == SEARCH) {
        if (inputArr.size() == 1) {
            throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
        }
        parseSearch(input);
    } else if (command == EDIT) {
        if (inputArr.size() == 1) {
            throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
        } else if (inputArr.size() > 2) {
            throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
        }
    } else if (command == DELETE) {
        if (inputArr.size() == 1) {
            throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
        } else if (inputArr.size() > 2) {
            throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
        }
    } else if (command == CLEAR) {
        if (inputArr.size() > 1) {
            throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
        }
    } else if (command == UNDO) {
        if (inputArr.size() > 1) {
            throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
        }
    }
}


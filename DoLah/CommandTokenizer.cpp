#include "CommandTokenizer.h"



CommandTokenizer::CommandTokenizer() {
}


CommandTokenizer::~CommandTokenizer() {
}

std::string CommandTokenizer::findCommand(std::vector<std::string> lineArr) {
    std::string command;
    if (TokenizerLibrary::inArray(commandList, lineArr.at(0))) {
        command = lineArr.at(0);
    } else {
        throw std::invalid_argument("command not recognized");
    }

    return command;
}

std::vector<std::string> CommandTokenizer::tokenize(std::string line) {
    std::vector<std::string> lineArr = TokenizerLibrary::explode(line, " ");

    std::string command = CommandTokenizer::findCommand(lineArr);
    
    if (command == commandList.at(0)) {

    }

    return {};
}


#include "CommandTokenizer.h"



CommandTokenizer::CommandTokenizer() {
}


CommandTokenizer::~CommandTokenizer() {
}


bool CommandTokenizer::isCommand(std::string str) {
    return std::find(commandList.begin(), commandList.end(), TokenizerLibrary::tolowercase(str)) != commandList.end();
}

std::vector<std::string> CommandTokenizer::tokenize(std::string line) {
    return {};
}


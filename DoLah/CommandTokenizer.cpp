#include "CommandTokenizer.h"



CommandTokenizer::CommandTokenizer() {
}


CommandTokenizer::~CommandTokenizer() {
}

std::vector<std::string> CommandTokenizer::tokenize(std::string line) {
    std::vector<std::string> lineArr = TokenizerLibrary::explode(line, " ");
    if (TokenizerLibrary::inArray(commandList, lineArr.at(0))) {

    }
    return {};
}


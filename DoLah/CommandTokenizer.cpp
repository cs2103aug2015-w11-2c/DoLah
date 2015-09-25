#include "CommandTokenizer.h"



CommandTokenizer::CommandTokenizer() {
}


CommandTokenizer::~CommandTokenizer() {
}

StringToken CommandTokenizer::findCommand(std::vector<std::string> lineArr) {
    StringToken output;
    if (TokenizerLibrary::inArray(commandList, lineArr.at(0))) {
        output.setData(lineArr.at(0));
    } else {
        throw std::exception("command not recognized");
    }

    return output;
}

std::vector<StringToken> CommandTokenizer::findTags(std::vector<std::string> lineArr) {
    std::vector<StringToken> output;

    std::vector<std::string> tags;
    std::vector<std::string> moretags;
    for (int i = 0; i < lineArr.size(); i++) {
        moretags = TokenizerLibrary::explode(lineArr.at(i), tag);
        moretags.erase(tags.begin());

    }
    for (int i = 0; i < tags.size(); i++) {
        tags.at(i) = TokenizerLibrary::tolowercase(tags.at(i));
    }




    return output;
}

std::vector<DateTimeToken> CommandTokenizer::findDate(std::vector<std::string> lineArr) {
    std::vector<DateTimeToken> output;

    return output;
}

std::vector<StringToken> CommandTokenizer::findDescription(std::vector<std::string> lineArr) {
    std::vector<StringToken> output;

    return output;
}

std::vector<std::string> CommandTokenizer::tokenize(std::string line) {
    std::vector<std::string> lineArr = TokenizerLibrary::explode(line, " ");
    StringToken command;
    try {
        command = CommandTokenizer::findCommand(lineArr);
    } catch (std::exception exception) {
        throw exception;
    }
    
    if (command.getData() == commandList.at(0)) {

    }

    return {};
}


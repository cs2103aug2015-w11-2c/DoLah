#include "CommandTokenizer.h"



CommandTokenizer::CommandTokenizer() {
}


CommandTokenizer::~CommandTokenizer() {
}

StringToken* CommandTokenizer::findCommand(std::vector<std::string> lineArr) {
    StringToken* output = new StringToken;
    if (TokenizerLibrary::inArray(commandList, lineArr.at(0))) {
        output->setData(lineArr.at(0));
    } else {
        throw std::exception("command not recognized");
    }

    return output;
}

StringToken* CommandTokenizer::findTags(std::vector<std::string> lineArr) {
    StringToken* tagToken = new StringToken;
    std::vector<std::string> tags;
    std::vector<std::string> moretags;
    
    for (size_t i = 0; i < lineArr.size(); i++) {
        moretags = TokenizerLibrary::explode(lineArr.at(i), tag);
        tags.insert(tags.begin(), moretags.begin()+1, moretags.end());
    }

    for (size_t i = 0; i < tags.size(); i++) {
        tags.at(i) = TokenizerLibrary::tolowercase(tags.at(i));
    }

    tags = TokenizerLibrary::stringVectorUnique(tags);
    tagToken->setData(tags);

    return tagToken;
}

DateTimeToken* CommandTokenizer::findDate(std::vector<std::string> lineArr) {
    DateTimeToken* output = new DateTimeToken;

    std::chrono::system_clock::time_point time;

    return output;
}

StringToken* CommandTokenizer::findDescription(std::vector<std::string> lineArr) {
    StringToken* output = new StringToken;

    lineArr.erase(lineArr.begin());
    output->setData(TokenizerLibrary::implode(lineArr, " "));

    return output;
}

std::vector<ITokenObject *> CommandTokenizer::tokenizeAdd(std::vector<std::string> lineArr) {
    std::vector<ITokenObject *> *out = new std::vector<ITokenObject *>;

    out->push_back(CommandTokenizer::findDescription(lineArr));
    out->push_back(CommandTokenizer::findTags(lineArr));
    out->push_back(CommandTokenizer::findDate(lineArr));

    return *out;
}

std::vector<std::string> CommandTokenizer::tokenize(std::string line) {
    std::vector<ITokenObject *> tokenizedLine;

    std::vector<std::string> lineArr = TokenizerLibrary::explode(line, " ");
    StringToken* command;
    try {
        command = CommandTokenizer::findCommand(lineArr);
    } catch (std::exception exception) {
        throw exception;
    }
    
    if (command->getData().at(0) == commandList.at(0)) {
        tokenizedLine = CommandTokenizer::tokenizeAdd(lineArr);
    }

    return {};
}


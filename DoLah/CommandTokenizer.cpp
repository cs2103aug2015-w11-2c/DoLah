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

std::vector<ITokenObject> CommandTokenizer::findTags(std::vector<std::string> lineArr) {
    std::vector<StringToken> tagTokenVector;
    std::vector<std::string> tags;
    std::vector<std::string> moretags;
    
    for (int i = 0; i < lineArr.size(); i++) {
        moretags = TokenizerLibrary::explode(lineArr.at(i), tag);
        tags.resize(tags.size() + moretags.size() - 1);
        merge(tags.begin(), tags.end(), moretags.begin() + 1, moretags.end(), tags);
    }

    for (int i = 0; i < tags.size(); i++) {
        tags.at(i) = TokenizerLibrary::tolowercase(tags.at(i));
    }

    tags = TokenizerLibrary::stringVectorUnique(tags);
    
    for (int i = 0; i < tags.size(); i++) {
        StringToken st;
        st.setData(tags.at(i));
        tagTokenVector.push_back(st);
    }

    return tagTokenVector;
}

DateTimeToken CommandTokenizer::findDate(std::vector<std::string> lineArr) {
    std::vector<DateTimeToken> output;

    return output;
}

StringToken CommandTokenizer::findDescription(std::vector<std::string> lineArr) {
    std::vector<StringToken> output;

    return output;
}

std::vector<ITokenObject> CommandTokenizer::tokenizeAdd(std::vector<std::string> lineArr) {
    std::vector<StringToken> tagTokenVector = CommandTokenizer::findTags(lineArr);

    std::vector<std::vector<ITokenObject *>> out;
    out.push_back(findDescription(lineArr));

    std::vector<ITokenObject *> test;
    test.push_back(new StringToken);


    // wait.. how to compile different kinds of token into one datastructure??
}

std::vector<std::string> CommandTokenizer::tokenize(std::string line) {
    std::vector<ITokenObject> tokenizedLine;

    std::vector<std::string> lineArr = TokenizerLibrary::explode(line, " ");
    StringToken command;
    try {
        command = CommandTokenizer::findCommand(lineArr);
    } catch (std::exception exception) {
        throw exception;
    }
    
    if (command.getData() == commandList.at(0)) {
        tokenizedLine = CommandTokenizer::tokenizeAdd(lineArr);
    }

    return {};
}


#include "CommandTokenizer.h"



CommandTokenizer::CommandTokenizer() {
}


CommandTokenizer::~CommandTokenizer() {
}

std::vector<std::string> CommandTokenizer::findCommand(std::vector<std::string> lineArr) {
    std::vector<std::string> output;
    if (TokenizerLibrary::inArray(commandList, lineArr.at(0))) {
        output.push_back(lineArr.at(0));
    } else {
        throw std::exception("command not recognized");
    }

    return output;
}

std::vector<std::string> CommandTokenizer::findTags(std::vector<std::string> lineArr) {
    std::vector<std::string> tags;
    std::vector<std::string> moretags;

    for (size_t i = 0; i < lineArr.size(); i++) {
        moretags = TokenizerLibrary::explode(lineArr.at(i), tag);
        tags.insert(tags.begin(), moretags.begin() + 1, moretags.end());
    }

    for (size_t i = 0; i < tags.size(); i++) {
        tags.at(i) = TokenizerLibrary::tolowercase(tags.at(i));
    }

    tags = TokenizerLibrary::stringVectorUnique(tags);

    return tags;
}

std::vector<std::chrono::system_clock::time_point> CommandTokenizer::findDate(std::vector<std::string> lineArr) {
    std::vector<std::chrono::system_clock::time_point> output;



    return output;
}

std::vector<std::string> CommandTokenizer::findDescription(std::vector<std::string> lineArr) {
    std::vector<std::string> output;

    lineArr.erase(lineArr.begin());
    output.push_back(TokenizerLibrary::implode(lineArr, " "));

    return output;
}

std::vector<int> CommandTokenizer::findPriority(std::vector<std::string> lineArr) {
    std::vector<int> output;

    return output;
}

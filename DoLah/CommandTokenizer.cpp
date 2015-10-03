#include "CommandTokenizer.h"



CommandTokenizer::CommandTokenizer() {
}


CommandTokenizer::~CommandTokenizer() {
}

std::string CommandTokenizer::findCommand(std::vector<std::string> lineArr) {
    std::vector<std::string> output;
    if (ParserLibrary::inArray(commandList, lineArr.at(0))) {
        return lineArr.at(0);
    }

    throw std::exception("command not recognized");
    return "";
}

std::vector<std::string> CommandTokenizer::findTags(std::vector<std::string> lineArr) {
    std::vector<std::string> tags;
    std::vector<std::string> moretags;

    for (size_t i = 0; i < lineArr.size(); i++) {
        moretags = ParserLibrary::explode(lineArr.at(i), tag);
        tags.insert(tags.begin(), moretags.begin() + 1, moretags.end());
    }

    for (size_t i = 0; i < tags.size(); i++) {
        tags.at(i) = ParserLibrary::tolowercase(tags.at(i));
    }

    tags = ParserLibrary::stringVectorUnique(tags);

    return tags;
}

std::vector<std::chrono::system_clock::time_point> CommandTokenizer::findDate(std::vector<std::string> lineArr) {
    std::vector<std::chrono::system_clock::time_point> output;



    return output;
}

std::string CommandTokenizer::findDescription(std::vector<std::string> lineArr) {
    std::string output;

    lineArr.erase(lineArr.begin());
    output = ParserLibrary::implode(lineArr, " ");

    return output;
}

int CommandTokenizer::findPriority(std::vector<std::string> lineArr) {
    int output = 100;

    return output;
}

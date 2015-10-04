#include "CommandTokenizer.h"



CommandTokenizer::CommandTokenizer() {
}


CommandTokenizer::~CommandTokenizer() {
}

std::string CommandTokenizer::findCommand(std::vector<std::string> lineArr) {
    std::string output;
    if (ParserLibrary::inStringArray(commandList, lineArr.at(0))) {
        output = lineArr.at(0);
    } else {
        throw std::invalid_argument(UNKNOWN_COMMAND_MESSAGE);
    }

    return output;
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

std::string CommandTokenizer::findDescription(std::vector<std::string> lineArr) {
    std::string output;

    lineArr.erase(lineArr.begin());
    output = ParserLibrary::implode(lineArr, " ");

    return output;
}

std::vector<std::chrono::system_clock::time_point> CommandTokenizer::findDate(std::vector<std::string> lineArr) {
    std::vector<std::chrono::system_clock::time_point> output;

    std::string datePattern = 
        "monday|tuesday|wednesday|thursday|friday|saturday|sunday"
        "|mon|tue|wed|thu|fri|sat|sun";
    std::string dayPattern = 
        "^([1-9]|0[1-9]|[1-2][0-9]|[3][0-1])(st|nd|rd|th|$)$";
    std::string monthPattern = 
        "january|february|march|april|may|june|july|august|september|october|november|december"
        "|jan|feb|mar|apr|may|jun|jul|aug|sep|oct|nov|dec"
        "|^([1-9]|0[1-9]|1[0-2])$";
    std::string yearPattern =
        "^2[0-1][0-9][0-9]|[0-9][0-9]$";


    for (size_t i = 0; i < lineArr.size(); i++) {
        if (ParserLibrary::inStringArray(timeSubCommandList, lineArr.at(i))) {

        }
    }

    return output;
}


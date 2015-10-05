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

    std::vector<std::string> description(lineArr.begin()+1, lineArr.end());
    output = ParserLibrary::implode(description, " ");

    return output;
}

bool CommandTokenizer::isDate(std::string str) {
    return false;
}

std::string stringRemove(std::string str, std::string substr) {
    size_t f = str.find(substr);
    str.replace(f, substr.length(), "");
    return str;
}

bool CommandTokenizer::isDay(std::string str) {
    std::string dayAppendixPattern = "(st|nd|rd|th)";
    str = std::regex_replace(str, std::regex(dayAppendixPattern), "");

    try {
        std::stoi(str);
    } catch (std::invalid_argument e) {
        return false;
    }
    return true;
}

int CommandTokenizer::getDay(std::string) {
    return 0;
}

bool CommandTokenizer::isMonth(std::string str) {
    return std::regex_match(str, std::regex(monthPattern, std::regex_constants::icase));
}

bool CommandTokenizer::isYear(std::string str) {
    try {
        std::stoi(str);
    } catch (std::invalid_argument e) {
        return false;
    }
    return true;
}

bool CommandTokenizer::isDateFormat(std::vector<std::string> strArr) {
    std::chrono::system_clock::time_point output;

    int day;
    int month;
    int year;

    int size = strArr.size();
    if (isDay(strArr.at(0))) {
        if (size <= 1) {
            return true;
        }
        if (isMonth(strArr.at(1))) {
            if (size <= 2) {
                return true;
            }
            if (isYear(strArr.at(2))) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else if (isMonth(strArr.at(0))) {
        if (size <= 1) {
            return false;
        }
        if (isDay(strArr.at(1))) {
            if (size <= 2) {
                return true;
            }
            if (isYear(strArr.at(2))) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

std::chrono::system_clock::time_point CommandTokenizer::DMYToTimePoint(std::vector<std::string> strArr) {


    return std::chrono::system_clock::time_point();
}

std::vector<std::chrono::system_clock::time_point> CommandTokenizer::findDate(std::vector<std::string> lineArr) {
    std::vector<std::chrono::system_clock::time_point> output;

    bool dateFlag = false;
    for (size_t i = lineArr.size()-1; i > 0 ; i--) {
        if (ParserLibrary::inStringArray(timeSubCommandList, lineArr.at(i))) {
            dateFlag = true;
        }
        if (dateFlag) {
            std::vector<std::string> subVec(lineArr.begin()+i, lineArr.end());
            if (isDateFormat(subVec)) {

            }
        }
    }

    return output;
}


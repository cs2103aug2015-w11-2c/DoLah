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

std::string stringRemove(std::string str, std::string substr) {
    size_t f = str.find(substr);
    str.replace(f, substr.length(), "");
    return str;
}

int CommandTokenizer::getDay(std::string str) {
    str = std::regex_replace(str, std::regex(dayAppendixPattern), "");

    if (str.length() > 2) {
        return NULL;
    } else if (!isDecimal(str)) {
        return NULL;
    }

    return std::stoi(str);
}

int CommandTokenizer::getMonth(std::string str) {
    std::string out;
    for (size_t m = 0; m < monthPattern.size(); m++) {
        if (std::regex_match(str, std::regex(monthPattern.at(m), std::regex_constants::icase))) {
            return m;
        }
    }

    return NULL;
}

int CommandTokenizer::getYear(std::string str) {
    if (str.length() != 2 && str.length() != 4) {
        return NULL;
    } else if (!isDecimal(str)) {
        return NULL;
    }

    return std::stoi(str);
}

bool CommandTokenizer::isDecimal(std::string str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (str.at(i) > '9' || str.at(i) < '0') {
            return false;
        }
    }
    return true;
}


std::tm CommandTokenizer::toDateFormat(std::vector<std::string> strArr) {
    time_t t = time(0);
    struct tm output;
    localtime_s(&output, &t);

    int day;
    int month;
    int year;

    int size = strArr.size();
    if ((day = getDay(strArr.at(0))) != NULL) {
        output.tm_mday = day;
        if (size <= 1) {
            return output;
        }
        if ((month = getMonth(strArr.at(1))) != NULL) {
            output.tm_mon = month;
            if (size <= 2) {
                return output;
            }
            if ((year = getYear(strArr.at(2))) != NULL) {
                output.tm_year = year - 1900;
                return output;
            } else {
                throw std::invalid_argument("");
            }
        } else {
            throw std::invalid_argument("");
        }
    } else if ((month = getMonth(strArr.at(0))) != NULL) {
        output.tm_mon = month;
        if (size <= 1) {
            throw std::invalid_argument("");
        }
        if ((day = getDay(strArr.at(1))) != NULL) {
            output.tm_mday = day;
            if (size <= 2) {
                return output;
            }
            if ((year = getYear(strArr.at(2))) != NULL) {
                output.tm_year = year - 1900;
                return output;
            } else {
                throw std::invalid_argument("");
            }
        } else {
            throw std::invalid_argument("");
        }
    } else {
        throw std::invalid_argument("");
    }
}

std::vector<std::tm> CommandTokenizer::findDate(std::vector<std::string> lineArr) {
    CommandTokenizer ct;

    std::vector<std::string> timeSubCommandList = { "on" };

    std::vector<std::tm> output;

    bool dateFlag = false;
    for (size_t i = lineArr.size() - 1; i > 0; i--) {
        if (ParserLibrary::inStringArray(timeSubCommandList, lineArr.at(i))) {
            dateFlag = true;
        }
        if (dateFlag) {
            std::vector<std::string> subVec(lineArr.begin() + i + 1, lineArr.end());
            try {
                output.push_back(ct.toDateFormat(subVec));
            } catch (std::invalid_argument e) {
                throw std::invalid_argument(ParserLibrary::implode(subVec, " "));
            }
        }
        dateFlag = false;
    }

    return output;
}


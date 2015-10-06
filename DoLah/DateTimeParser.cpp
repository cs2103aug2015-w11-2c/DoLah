#include "DateTimeParser.h"

std::string DateTimeParser::relativePattern = "this|next";
std::string DateTimeParser::datePattern = "^("
        "monday|tuesday|wednesday|thursday|friday|saturday|sunday"
        "|mon|tue|wed|thu|fri|sat|sun"
        ")$";
std::string DateTimeParser::dayPattern = "^("
        "([1-9]|0[1-9]|[1-2][0-9]|[3][0-1])(st|nd|rd|th|$)"
        ")$";
std::string DateTimeParser::dayAppendixPattern = "(st|nd|rd|th)$";
std::vector<std::string> DateTimeParser::monthPattern = {
    "^(january|jan|01|1)$",
    "^(february|feb|02|2)$",
    "^(march|mar|03|3)$",
    "^(april|apr|04|4)$",
    "^(may|05|5)$",
    "^(june|jun|06|6)$",
    "^(july|jul|07|7)$",
    "^(august|aug|08|8)$",
    "^(september|sep|09|9)$",
    "^(october|oct|10)$",
    "^(november|nov|11)$",
    "^(december|dec|12)$"
};

std::vector<std::string> DateTimeParser::monthFormat = {
    "^(january|jan|1|01)$",
};


DateTimeParser::DateTimeParser() {
}


DateTimeParser::~DateTimeParser() {
}



int DateTimeParser::getDay(std::string str) {
    str = std::regex_replace(str, std::regex(dayAppendixPattern), "");

    if (str.length() > 2) {
        return NULL;
    } else if (!ParserLibrary::isDecimal(str)) {
        return NULL;
    }

    return std::stoi(str);
}

int DateTimeParser::getMonth(std::string str) {
    std::string out;
    for (size_t m = 0; m < monthPattern.size(); m++) {
        if (std::regex_match(str, std::regex(monthPattern.at(m), std::regex_constants::icase))) {
            return m;
        }
    }

    return NULL;
}

int DateTimeParser::getYear(std::string str) {
    if (str.length() != 2 && str.length() != 4) {
        return NULL;
    } else if (!ParserLibrary::isDecimal(str)) {
        return NULL;
    }

    return std::stoi(str);
}

std::tm DateTimeParser::toDateFormat(std::vector<std::string> strArr) {
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

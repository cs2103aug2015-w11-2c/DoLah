#include "DateTimeParser.h"

namespace DoLah {

    std::vector<std::string> DateTimeParser::decorators = { "of" };

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
                return (int) m;
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
        std::vector<std::string> cleanArr = strArr;
        if (cleanArr.size() == 1) {
            std::string str = cleanArr.at(0);
            cleanArr = ParserLibrary::explode(str, "-");
        } else {
            cleanArr = ParserLibrary::removeElementsFromStringVector(strArr, decorators);
        }

        return classifyDate(cleanArr);
    }

    std::string DateTimeParser::tmToString(std::tm time) {
        return std::to_string(time.tm_mday) + "/" + std::to_string(time.tm_mon + 1) + "/" + std::to_string(time.tm_year + 1900);
    }

    std::tm DateTimeParser::classifyDate(std::vector<std::string> strArr) {
        std::tm output;
        try {
            output = checkDMY(strArr);
        } catch (std::invalid_argument e) {
            try {
                output = checkMDY(strArr);
            } catch (std::invalid_argument e) {
                throw e;
            }
        }
        return output;
    }

    std::tm DateTimeParser::checkDMY(std::vector<std::string> strArr) {
        time_t t = time(0);
        std::tm output;
        localtime_s(&output, &t);

        int day;
        int month;
        int year;

        size_t size = strArr.size();
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
        }
        return std::tm();
    }

    std::tm DateTimeParser::checkMDY(std::vector<std::string> strArr) {
        time_t t = time(0);
        std::tm output;
        localtime_s(&output, &t);

        int day;
        int month;
        int year;

        size_t size = strArr.size();
        if ((month = getMonth(strArr.at(0))) != NULL) {
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
        return std::tm();
    }
}
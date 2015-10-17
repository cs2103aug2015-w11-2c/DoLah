#include "DateTimeParser.h"

namespace DoLah {
    int DateTimeParser::REJECT = -1;
    std::string DateTimeParser::CENTURY = "20";

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
    std::vector<std::string> DateTimeParser::dateDividers = {
        "/", "-", "."
    };

    DateTimeParser::DateTimeParser() {
    }


    DateTimeParser::~DateTimeParser() {
    }



    int DateTimeParser::getDay(std::string str) {
        str = std::regex_replace(str, std::regex(dayAppendixPattern), "");

        if (str.length() > 2) {
            return REJECT;
        } else if (!ParserLibrary::isDecimal(str)) {
            return REJECT;
        }

        return std::stoi(str);
    }

    int DateTimeParser::getMonth(std::string str) {
        std::string out;
        for (size_t m = 0; m < monthPattern.size(); m++) {
            if (std::regex_match(str, std::regex(monthPattern.at(m), std::regex_constants::icase))) {
                return (int)m;
            }
        }

        return REJECT;
    }

    int DateTimeParser::getYear(std::string str) {
        std::string year = str;
        if (year.length() != 2 && year.length() != 4) {
            return REJECT;
        } else if (!ParserLibrary::isDecimal(year)) {
            return REJECT;
        }

        if (year.length() == 2) {
            year = CENTURY + year;
        }

        return std::stoi(year);
    }



    std::tm DateTimeParser::toDateFormat(std::vector<std::string> strArr) {
        std::tm output;

        std::vector<std::string> cleanArr = strArr;
        if (cleanArr.size() == 1) {
            std::string str = cleanArr.at(0);
            for (size_t i = 0; i < dateDividers.size(); i++) {
                cleanArr = ParserLibrary::explode(str, dateDividers.at(i));
                if (cleanArr.size() > 1) {
                    break;
                }
            }
        }
        cleanArr = ParserLibrary::removeElementsFromStringVector(cleanArr, decorators);

        try {
            output = classifyDate(cleanArr);
        } catch (std::invalid_argument e) {
            throw e;
        }

        return output;
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

        int day = -1;
        int month = -1;
        int year = -1;

        size_t size = strArr.size();
        if ((day = getDay(strArr.at(0))) != REJECT) {
            output.tm_mday = day;
            if (size <= 1) {
                return output;
            }
            if ((month = getMonth(strArr.at(1))) != REJECT) {
                output.tm_mon = month;
                if (size <= 2) {
                    return output;
                }
                if ((year = getYear(strArr.at(2))) != REJECT) {
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
        return output;
    }

    std::tm DateTimeParser::checkMDY(std::vector<std::string> strArr) {
        time_t t = time(0);
        std::tm output;
        localtime_s(&output, &t);

        int day = -1;
        int month = -1;
        int year = -1;

        size_t size = strArr.size();
        if ((month = getMonth(strArr.at(0))) != REJECT) {
            output.tm_mon = month;
            if (size <= 1) {
                throw std::invalid_argument("");
            }
            if ((day = getDay(strArr.at(1))) != REJECT) {
                output.tm_mday = day;
                if (size <= 2) {
                    return output;
                }
                if ((year = getYear(strArr.at(2))) != REJECT) {
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
        return output;
    }
}
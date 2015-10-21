#include "DateTimeParser.h"

namespace DoLah {
    int DateTimeParser::REJECT = -1;
    std::string DateTimeParser::CENTURY = "20";
    int DateTimeParser::DAYINSECS = 86400;
    int DateTimeParser::WEEKINSECS = 604800;
    int DateTimeParser::MONTHINSECS = 2592000;

    std::vector<std::string> DateTimeParser::decorators = { "of" };

    std::string DateTimeParser::relativePattern = "this|next";
    std::string DateTimeParser::modiferPattern = "^(next |coming |)";
    std::vector<std::string> DateTimeParser::datePattern = {
        "monday|mon|mond",
        "tuesday|tue|tues",
        "wednesday|wed|weds",
        "thursday|thu|thur",
        "friday|fri|frid",
        "saturday|sat|satu",
        "sunday|sun|sund"
    };
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

    int DateTimeParser::getYear(std::string year) {
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

    int DateTimeParser::getDate(std::string str) {
        std::string out;
        for (size_t d = 0; d < datePattern.size(); d++) {
            if (std::regex_match(str, std::regex(datePattern.at(d), std::regex_constants::icase))) {
                return (int)d;
            }
        }

        return REJECT;
    }

    int DateTimeParser::getDateModifier(int date, bool notThisWeek) {
        time_t t = time(0);
        std::tm current;
        localtime_s(&current, &t);

        int diff = date - current.tm_wday + 1;
        if (diff < 0) {
            diff = 7 + diff;
        } else if (notThisWeek) {
            diff += 7;
        }

        return diff;
    }

    std::tm DateTimeParser::checkModifierFormat(std::vector<std::string> strArr) {
        std::tm output;
        int dayDiff = 0;
        int weekDiff = 0;
        int monthDiff = 0;

        int size = strArr.size();

        int index = 0;
        std::string element;
        
        element = strArr.at(index);
        if (ParserLibrary::isDecimal(element) || element == "a") {
            int n;
            if (element == "a") {
                n = 1;
            } else {
                n = stoi(element);
            }

            element = strArr.at(++index);
            
            if (ParserLibrary::inStringArray({ "day", "days" }, element)) {
                dayDiff = n;
            } else if (ParserLibrary::inStringArray({ "week", "weeks" }, element)) {
                weekDiff = n;
            } else if (ParserLibrary::inStringArray({ "month", "months" }, element)) {
                monthDiff = n; // month length is not fixed!!
            }
        } else if (element == "next") {
            if (size < 2) {
                throw std::invalid_argument("");
            }
            element = strArr.at(1);
            int date = getDate(element);
            if (date != REJECT) {
                dayDiff = getDateModifier(date, true);
            }
        } else if (strArr.size() == 1) {
            element = strArr.at(0);
            int date = getDate(element);
            if (date != REJECT) {
                dayDiff = getDateModifier(date, false);
            }
        } else {
            throw std::invalid_argument("");
        }

        int modifer = dayDiff * DAYINSECS + weekDiff * WEEKINSECS + monthDiff * MONTHINSECS;
        time_t t = time(NULL) + modifer;
        localtime_s(&output, &t);

        return output;
    }

    std::tm DateTimeParser::toDateFormat(std::vector<std::string> strArr) {
        std::tm output;

        try {
            output = checkModifierFormat(strArr);
            return output;
        } catch (std::invalid_argument e) {
            // if not continue
        }

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

    std::tm DateTimeParser::classifyDate(std::vector<std::string> strArr) {
        std::tm output;
        try {
            output = checkDMYformat(strArr);
        } catch (std::invalid_argument e) {
            try {
                output = checkMDYformat(strArr);
            } catch (std::invalid_argument e) {
                throw e;
            }
        }
        return output;
    }

    std::tm DateTimeParser::checkDMYformat(std::vector<std::string> strArr) {
        time_t t = time(0);
        std::tm output;
        localtime_s(&output, &t);

        int day = -1;
        int month = -1;
        int year = -1;

        size_t size = strArr.size();
        day = getDay(strArr.at(0));
        if (day != REJECT) {
            output.tm_mday = day;
            if (size <= 1) {
                return output;
            }
            month = getMonth(strArr.at(1));
            if (month != REJECT) {
                output.tm_mon = month;
                if (size <= 2) {
                    return output;
                }
                year = getYear(strArr.at(2));
                if (year != REJECT) {
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

    std::tm DateTimeParser::checkMDYformat(std::vector<std::string> strArr) {
        time_t t = time(0);
        std::tm output;
        localtime_s(&output, &t);

        int day = -1;
        int month = -1;
        int year = -1;

        size_t size = strArr.size();
        month = getMonth(strArr.at(0));
        if (month != REJECT) {
            output.tm_mon = month;
            if (size <= 1) {
                throw std::invalid_argument("");
            }
            day = getDay(strArr.at(1));
            if (day != REJECT) {
                output.tm_mday = day;
                if (size <= 2) {
                    return output;
                }
                year = getYear(strArr.at(2));
                if (year != REJECT) {
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
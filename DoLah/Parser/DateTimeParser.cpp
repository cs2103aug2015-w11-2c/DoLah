//@@author A0116722M
#include "DateTimeParser.h"

namespace DoLah {
    int DateTimeParser::REJECT = -1;
    std::string DateTimeParser::CENTURY = "20";
    int DateTimeParser::MIN_IN_SECS = 60;
    int DateTimeParser::HOUR_IN_SECS = 3600;
    int DateTimeParser::DAY_IN_SECS = 86400;
    int DateTimeParser::WEEK_IN_SECS = 604800;
    int DateTimeParser::MONTH_IN_SECS = 2592000;
    int DateTimeParser::DEFAULT_TIME = 1439; // 23:59

    std::vector<std::string> DateTimeParser::DECORATORS = { "of", "in", "on", "by", "due", "at" };

    std::vector<std::string> DateTimeParser::DATE_PATTERN = {
        "monday|mon|mond",
        "tuesday|tue|tues",
        "wednesday|wed|weds",
        "thursday|thu|thur",
        "friday|fri|frid",
        "saturday|sat|satu",
        "sunday|sun|sund"
    };
    std::string DateTimeParser::DAY_APPENDIX_PATTERN = "(st|nd|rd|th)$";
    std::vector<std::string> DateTimeParser::MONTH_PATTERN = {
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
    std::vector<std::string> DateTimeParser::DATE_DIVIDERS = { "/", "-", "." };
    std::vector<std::string> DateTimeParser::PUNCTUATIONS = { "," };

    std::vector<std::string> DateTimeParser::TODAY_INDICATORS = { "today", "td" };
    std::vector<std::string> DateTimeParser::TOMORROW_INDICATORS = { "tomorrow", "tom", "tmr" };
    std::vector<std::string> DateTimeParser::SINGULAR_FORMATS = { "a", "an", "the", "one" };

    std::vector<std::string> DateTimeParser::DAY_DESCRIPTION_INDICATOR = { "d", "day", "days" };
    std::vector<std::string> DateTimeParser::WEEK_DESCRIPTION_INDICATOR = { "w", "week", "weeks", "wk", "wks" };
    std::vector<std::string> DateTimeParser::MONTH_DESCRIPTION_INDICATOR = { "m", "month", "months", "mon", "mons" };
    std::vector<std::string> DateTimeParser::YEAR_DESCRIPTION_INDICATOR = { "y", "year", "years", "yr", "yrs" };
    std::vector<std::string> DateTimeParser::HOUR_DESCRIPTION_INDICATOR = { "hour", "hours", "hr", "hrs" };
    std::vector<std::string> DateTimeParser::MIN_DESCRIPTION_INDICATOR = { "minute", "minutes", "min", "mins" };

    std::vector<std::string> DateTimeParser::NEXT_FORMATS = { "next", "coming" };

    std::string DateTimeParser::AM = "am";
    std::string DateTimeParser::PM = "pm";
    std::string DateTimeParser::TIME_DIVIDERS = ":";

    DateTimeParser::DateTimeParser() {
    }


    DateTimeParser::~DateTimeParser() {
    }



    int DateTimeParser::getDay(std::string str) {
        str = std::regex_replace(str, std::regex(DAY_APPENDIX_PATTERN), "");

        if (str.length() > 2) {
            return REJECT;
        } else if (!ParserLibrary::isDecimal(str)) {
            return REJECT;
        }

        return std::stoi(str);
    }

    int DateTimeParser::getMonth(std::string str) {
        std::string out;
        for (size_t m = 0; m < MONTH_PATTERN.size(); m++) {
            if (std::regex_match(str, std::regex(MONTH_PATTERN.at(m), std::regex_constants::icase))) {
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
        for (size_t d = 0; d < DATE_PATTERN.size(); d++) {
            if (std::regex_match(str, std::regex(DATE_PATTERN.at(d), std::regex_constants::icase))) {
                return (int)d;
            }
        }

        return REJECT;
    }

    int DateTimeParser::getTime(std::string str) {
        str = ParserLibrary::tolowercase(str);

        int time = 0;
        bool isTime = false;

        bool isPM = false;
        bool isAM = false;
        if (str.find(PM) != std::string::npos) {
            ParserLibrary::stringRemove(str, PM);
            isPM = true;
            isTime = true;
        } else if (str.find(AM) != std::string::npos) {
            ParserLibrary::stringRemove(str, AM);
            isAM = true;
            isTime = true;
        }
        
        std::vector<std::string> strArr = ParserLibrary::explode(str, TIME_DIVIDERS);

        int hour = std::stoi(strArr.at(0));
        if (isAM) {
            if (hour > 12) {
                throw std::invalid_argument("");
            } else if (isAM && hour == 12) {
                hour = 0;
            }
        }

        time = hour * 60;

        if (isPM) {
            if (hour < 12) {
                time += 12 * 60;
            }
        }

        if (strArr.size() > 1) {
            time += std::stoi(strArr.at(1));
            isTime = true;
        }

        if (!isTime) {
            throw std::invalid_argument("");
        }

        return time;
    }

    int DateTimeParser::getDateModifier(int date, bool notThisWeek) {
        std::tm current = TimeManager::getCurrentTime();

        int diff = date - current.tm_wday + 1;
        if (diff < 0) {
            diff = 7 + diff;
        } else if (notThisWeek) {
            diff += 7;
        }

        return diff;
    }

    int DateTimeParser::checkTimeModifier(std::vector<std::string> strArr) {
        int hourDiff = 0;
        int minDiff = 0;

        size_t size = strArr.size();

        int index = 0;
        std::string element;

        element = strArr.at(index++);

        if (size == 2) {
            if (ParserLibrary::inStringArray(NEXT_FORMATS, element)) { // next pattern
                element = strArr.at(index++);
                if (ParserLibrary::inStringArray(HOUR_DESCRIPTION_INDICATOR, element)) {
                    hourDiff = 1;
                } else if (ParserLibrary::inStringArray(MIN_DESCRIPTION_INDICATOR, element)) {
                    minDiff = 1;
                } else {
                    throw std::invalid_argument("");
                }
            } else if (ParserLibrary::isDecimal(element) ||
                ParserLibrary::inStringArray(SINGULAR_FORMATS, element)) { // 10 days, a week, etc
                int n = 0;
                if (ParserLibrary::inStringArray(SINGULAR_FORMATS, element)) {
                    n = 1;
                } else {
                    n = stoi(element);
                }

                element = strArr.at(index++);
                if (ParserLibrary::inStringArray(HOUR_DESCRIPTION_INDICATOR, element)) {
                    hourDiff = n;
                } else if (ParserLibrary::inStringArray(MIN_DESCRIPTION_INDICATOR, element)) {
                    minDiff = n;
                } else {
                    throw std::invalid_argument("");
                }
            } else {
                throw std::invalid_argument("");
            }
        } else {
            throw std::invalid_argument("");
        }

        std::tm current = TimeManager::getCurrentTime();
        std::tm modified = current;
        modified.tm_hour += hourDiff;
        modified.tm_min += minDiff;

        return TimeManager::compareTime(current, modified);
    }

    int DateTimeParser::checkDateModifier(std::vector<std::string> strArr, std::tm lowerBound) {
        int modifier = 0;
        std::tm current = TimeManager::getCurrentTime();

        int dayDiff = 0;
        int weekDiff = 0;
        int monthDiff = 0;
        int yearDiff = 0;

        size_t size = strArr.size();

        int index = 0;
        std::string element;

        element = strArr.at(index++);
        int date = getDate(element);
        if (size == 1) { // singleton format
            if (ParserLibrary::inStringArray(TODAY_INDICATORS, element)) {
                dayDiff = 0;
            } else if (ParserLibrary::inStringArray(TOMORROW_INDICATORS, element)) {
                dayDiff = 1;
            } else if (date != REJECT) {
                dayDiff = getDateModifier(date, false);
                
                std::tm modifiedDate = current;
                modifiedDate.tm_mday += dayDiff;
                mktime(&modifiedDate);
                modifier = TimeManager::compareTime(lowerBound, modifiedDate);
                if (modifier > 0) {
                    return modifier;
                } else {
                    modifiedDate.tm_mday += 7;
                    modifier = TimeManager::compareTime(current, modifiedDate);
                    return modifier;
                }
            } else {
                throw std::invalid_argument("");
            }
        } else if (size == 2) {
            if (ParserLibrary::inStringArray(NEXT_FORMATS, element)) { // next pattern
                element = strArr.at(index++);
                int date = getDate(element);
                if (date != REJECT) {
                    dayDiff = getDateModifier(date, true);
                } else {
                    if (ParserLibrary::inStringArray(DAY_DESCRIPTION_INDICATOR, element)) {
                        dayDiff = 1;
                    } else if (ParserLibrary::inStringArray(WEEK_DESCRIPTION_INDICATOR, element)) {
                        weekDiff = 1;
                    } else if (ParserLibrary::inStringArray(MONTH_DESCRIPTION_INDICATOR, element)) {
                        monthDiff = 1;
                    } else if (ParserLibrary::inStringArray(YEAR_DESCRIPTION_INDICATOR, element)) {
                        yearDiff = 1;
                    } else {
                        throw std::invalid_argument("");
                    }
                }
            } else if (ParserLibrary::isDecimal(element) ||
                ParserLibrary::inStringArray(SINGULAR_FORMATS, element)) { // 10 days, a week, etc
                int n = 0;
                if (ParserLibrary::inStringArray(SINGULAR_FORMATS, element)) {
                    n = 1;
                } else {
                    n = stoi(element);
                }

                element = strArr.at(index++);
                if (ParserLibrary::inStringArray(DAY_DESCRIPTION_INDICATOR, element)) {
                    dayDiff = n;
                } else if (ParserLibrary::inStringArray(WEEK_DESCRIPTION_INDICATOR, element)) {
                    weekDiff = n;
                } else if (ParserLibrary::inStringArray(MONTH_DESCRIPTION_INDICATOR, element)) {
                    monthDiff = n;
                } else if (ParserLibrary::inStringArray(YEAR_DESCRIPTION_INDICATOR, element)) {
                    yearDiff = n;
                } else {
                    throw std::invalid_argument("");
                }
            } else {
                throw std::invalid_argument("");
            }
        } else if (date != REJECT) {
            dayDiff = getDateModifier(date, false);
            std::vector<std::string> subVec(strArr.begin() + 1, strArr.end());

            subVec = formatArr(subVec);
            std::tm specifiedDay = classifyDate(subVec);

            if (TimeManager::compareTime(lowerBound, specifiedDay) < 0) {
                specifiedDay.tm_mday += 7;
                mktime(&specifiedDay);
            }

            modifier = TimeManager::compareTime(current, specifiedDay);;
            return modifier;
        } else {
            throw std::invalid_argument("");
        }

        std::tm modified = current;
        modified.tm_mday += dayDiff + 7 * weekDiff;
        modified.tm_mon += monthDiff;
        modified.tm_year += yearDiff;

        return TimeManager::compareTime(current, modified);
    }

    std::vector<std::string> DateTimeParser::formatArr(std::vector<std::string> strArr) {
        std::vector<std::string> cleanArr = ParserLibrary::removeElementsFromStringVector(strArr, DECORATORS);

        for (size_t i = 0; i < cleanArr.size(); i++) {
            for (size_t j = 0; j < PUNCTUATIONS.size(); j++) {
                boost::erase_all(cleanArr.at(i), PUNCTUATIONS.at(j));
            }
        }

        if (cleanArr.size() == 1) {
            std::string str = cleanArr.at(0);

            for (size_t i = 0; i < DATE_DIVIDERS.size(); i++) {
                cleanArr = ParserLibrary::explode(str, DATE_DIVIDERS.at(i));
                if (cleanArr.size() > 1) {
                    break;
                }
            }
        }

        if (cleanArr.size() == 0) {
            throw std::invalid_argument("");
        }

        return cleanArr;
    }

    std::tm DateTimeParser::toDateFormat(std::vector<std::string> strArr, std::tm lowerBound) {
        std::tm output = std::tm();

        bool done = false;
        bool hasTime = false;
        bool hasDay = false;

        bool hasLowerBound = (lowerBound.tm_year != std::tm().tm_year);
        if (hasLowerBound) {
            output = lowerBound;
            hasDay = true;
        } else {
            lowerBound = TimeManager::getCurrentTime();
        }

        std::vector<std::string> cleanArr = formatArr(strArr);

        int giventime = DEFAULT_TIME;
        for (size_t i = 0; i < cleanArr.size(); i++) {
            try {
                giventime = getTime(cleanArr.at(i));
                cleanArr.erase(cleanArr.begin() + i);
                if (cleanArr.size() == 0) {
                    done = true;
                }
                hasTime = true;
                break;
            } catch (std::invalid_argument e) {
                // if not continue
            }
        }

        if (!done) {
            try {
                int modifier = checkDateModifier(cleanArr, lowerBound);
                time_t t = time(NULL) + modifier;
                localtime_s(&output, &t);
                if (!TimeManager::isValidDate(output)) {
                    throw std::invalid_argument("");
                }
                done = true;
                hasDay = true;
            } catch (std::invalid_argument e) {
                // if not continue
            }
        }

        if (!done) {
            try {
                int modifier = checkTimeModifier(cleanArr);
                time_t t = time(NULL) + modifier;
                localtime_s(&output, &t);
                if (!TimeManager::isValidDate(output)) {
                    throw std::invalid_argument("");
                }
                done = true;

                giventime = output.tm_hour * 60 + output.tm_min;

                hasTime = true;
            } catch (std::invalid_argument e) {
                // if not continue
            }
        }

        if (!done) {
            try {
                output = classifyDate(cleanArr);
                hasTime = true;
                hasDay = true;
            } catch (std::invalid_argument e) {
                // if not continue
            }
        }

        output.tm_hour = giventime / 60;
        output.tm_min = giventime % 60;
        output.tm_sec = 0; // default

        // If only time is given and the time is behind the lowerBound,
        // take it as the next day.
        if (!hasDay && !hasTime) {
            throw std::invalid_argument("");
        } else if (!hasDay) {
            output = TimeManager::copyDay(TimeManager::getCurrentTime(), output);
            if (TimeManager::compareTime(lowerBound, output) < 0) {
                output.tm_mday += 1;
            }
        }

        std::mktime(&output);
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
        std::tm current = TimeManager::getCurrentTime();
        std::tm output = current;

        int day = -1;
        int month = -1;
        int year = -1;

        int monthModifier = 0;
        int yearModifier = 0;

        size_t size = strArr.size();
        day = getDay(strArr.at(0));
        month = getMonth(strArr.at(0));
        if (day != REJECT) {
            output.tm_mday = day;
            if (size > 1) {
                month = getMonth(strArr.at(1));
                if (month != REJECT) {
                    output.tm_mon = month;
                    if (size > 2) {
                        year = getYear(strArr.at(2));
                        if (year != REJECT) {
                            output.tm_year = year - 1900;
                        } else {
                            throw std::invalid_argument("");
                        }
                    } else {
                        if (current.tm_mon > month) {
                            yearModifier += 1;
                        }
                    }
                } else {
                    throw std::invalid_argument("");
                }
            } else {
                if (current.tm_mday > day) {
                    monthModifier += 1;
                }
            }
        } else if (month != REJECT) {
            output.tm_mday = 1;
            output.tm_mon = month;
            if (size > 1) {
                year = getYear(strArr.at(1));
                if (year != REJECT) {
                    output.tm_year = year - 1900;
                } else {
                    throw std::invalid_argument("");
                }
            } else {
                if (current.tm_mon > month) {
                    yearModifier += 1;
                }
            }
        } else {
            throw std::invalid_argument("");
        }

        if (!TimeManager::isValidDate(output)) {
            throw std::invalid_argument("");
        }

        output.tm_mon += monthModifier;
        output.tm_year += yearModifier;

        return output;
    }

    std::tm DateTimeParser::checkMDYformat(std::vector<std::string> strArr) {
        std::tm current = TimeManager::getCurrentTime();
        std::tm output = current;

        int day = -1;
        int month = -1;
        int year = -1;

        int monthModifier = 0;
        int yearModifier = 0;

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
                if (size > 2) {
                    year = getYear(strArr.at(2));
                    if (year != REJECT) {
                        output.tm_year = year - 1900;
                    } else {
                        throw std::invalid_argument("");
                    }
                } else {
                    if (current.tm_mon > month) {
                        yearModifier += 1;
                    }
                }
            } else {
                throw std::invalid_argument("");
            }
        } else {
            throw std::invalid_argument("");
        }

        if (!TimeManager::isValidDate(output)) {
            throw std::invalid_argument("");
        }

        output.tm_mon += monthModifier;
        output.tm_year += yearModifier;

        return output;
    }
}
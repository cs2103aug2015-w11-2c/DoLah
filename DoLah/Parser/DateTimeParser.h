#pragma once

#include <string>
#include <vector>
#include <regex>
#include <iterator>

#include "boost/algorithm/string.hpp"

#include "ParserLibrary.h"


namespace DoLah {
    class DateTimeParser {
    public:
        DateTimeParser();
        ~DateTimeParser();

        // decision tree to classify the input as dateformat or not
        // accepts DD, DD MM, DD MM YYYY, MM DD, MM DD YYYY
        static std::tm toDateFormat(std::vector<std::string>);
        static int getDay(std::string);
        static int getMonth(std::string);
        static int getYear(std::string);
        static int getDate(std::string);
        
        static int getDateModifier(int, bool);
        static std::tm checkModifierFormat(std::vector<std::string>);

        static std::tm classifyDate(std::vector<std::string>);
        // 25th December 2015
        static std::tm checkDMYformat(std::vector<std::string>);
        // December 25th 2015
        static std::tm checkMDYformat(std::vector<std::string>);
    private:
        static int REJECT;
        static std::string CENTURY;
        static int DAYINSECS;
        static int WEEKINSECS;
        static int MONTHINSECS;

        // this week, next week (not implemented)
        static std::string relativePattern;
        static std::string modiferPattern;
        static std::vector<std::string> datePattern;
        static std::string dayPattern;
        static std::vector<std::string> monthPattern;

        // 1st, 2nd, 3rd, 4th
        static std::string dayAppendixPattern;
        // 25th of December 2015
        static std::vector<std::string> decorators;
        static std::vector<std::string> punctuations;
        // 25/12/2015, 25-12-2015, 25.12.2015,
        static std::vector<std::string> dateDividers;

        static std::vector<std::string> tomorrowPattern;
        static std::vector<std::string> articlePattern;
        static std::vector<std::string> dayDescriptionPattern;
        static std::vector<std::string> weekDescriptionPattern;
        static std::vector<std::string> monthDescriptionPattern;
        static std::vector<std::string> nextPattern;
    };
}
#pragma once

#include <string>
#include <vector>
#include <regex>
#include <iterator>

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
        static std::string tmToString(std::tm);
        static std::tm classifyDate(std::vector<std::string>);
        static std::tm checkDMY(std::vector<std::string>);
        static std::tm checkMDY(std::vector<std::string>);
    private:
        static int REJECT;
        static std::string relativePattern;
        static std::string datePattern;
        static std::string dayPattern;
        static std::string dayAppendixPattern;
        static std::vector<std::string> monthPattern;
        static std::vector<std::string> decorators;
        static std::vector<std::string> dateDividers;
    };
}
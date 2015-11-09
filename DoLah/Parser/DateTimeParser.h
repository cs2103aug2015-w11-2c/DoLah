#pragma once

/**
 * @class DateTimeParser.h Parser/DateTimeParser.h
 * @brief Static library to handle conversion from string vector to std::tm.
 *
 * Static library to handle conversion from string vector to std::tm.
 * Throws invalid_argument exception if the given list of string cannot be converted.
 */

#include <string>
#include <vector>
#include <regex>
#include <iterator>

#include "boost/algorithm/string/erase.hpp"

#include "ParserLibrary.h"
#include "TimeManager.h"

namespace DoLah {
    class DateTimeParser {
    public:
        DateTimeParser();
        ~DateTimeParser();

        /**
         * Converts string array into std::tm.
         * It will handle many different kinds of formats for a degree of NLP.
         * @param[in]   strArr String array to be converted
         * @param[in]   lowerBound std::tm that indicates the lowerbound for the time.
         *              By default, the current time is set as the lowerbound.
         * @return std::tm object
         */
        static std::tm toDateFormat(std::vector<std::string>, std::tm = std::tm());

        /**
         * Check the input string and convert it into corresponding day.
         * If not valid, global variable int REJECT will be returned.
         * @param[in]   str String to be converted
         * @return Day int
         */
        static int getDay(std::string);

        /**
         * Check the input string and convert it into corresponding month.
         * If not valid, global variable int REJECT will be returned.
         * @param[in]   str String to be converted
         * @return Month int
         */
        static int getMonth(std::string);

        /**
         * Check the input string and convert it into corresponding year.
         * If not valid, global variable int REJECT will be returned.
         * @param[in]   str String to be converted
         * @return Year int
         */
        static int getYear(std::string);

        /**
         * Check the input string and convert it into corresponding int that represents the date.
         * If not valid, global variable int REJECT will be returned.
         * @param[in]   str String to be converted
         * @return Date int
         */
        static int getDate(std::string);

        /**
         * Check the input string and convert it into corresponding time represented as seconds since the Epoch.
         * If not valid, global variable int REJECT will be returned.
         * @param[in]   str String to be converted
         * @return Time int
         */
        static int getTime(std::string);

        /**
         * Removes unnecessary elements that is unrelated to date time parsing from the string array.
         * @param[in]   strArr String vector to be formatted
         * @return Formatted string vector
         */
        static std::vector<std::string> formatArr(std::vector<std::string>);

        // Date provides an indirect indication to a certain day.
        // Add modifier to the current day to find that day.
        static int getDateModifier(int, bool);

        // Time that is relative to today such as in 10 days, in a week, tomorrow
        static int checkDateModifier(std::vector<std::string>, std::tm);

        static int checkTimeModifier(std::vector<std::string>);

        static std::tm classifyDate(std::vector<std::string>);
        // 25th December 2015
        static std::tm checkDMYformat(std::vector<std::string>);
        // December 25th 2015
        static std::tm checkMDYformat(std::vector<std::string>);
    private:
        static int REJECT;
        static std::string CENTURY;
        static int MININSECS;
        static int HOURINSECS;
        static int DAYINSECS;
        static int WEEKINSECS;
        static int MONTHINSECS;
        static int DEFAULT_TIME;

        // this week, next week (not implemented)
        static std::string relativePattern;
        static std::vector<std::string> datePattern;
        static std::vector<std::string> monthPattern;

        // 1st, 2nd, 3rd, 4th
        static std::string dayAppendixPattern;
        // 25th of December 2015
        static std::vector<std::string> decorators;
        // Sunday, 17th of March
        static std::vector<std::string> punctuations;
        // 25/12/2015, 25-12-2015, 25.12.2015,
        static std::vector<std::string> dateDividers;

        // today
        static std::vector<std::string> todayPattern;
        // tomorrow
        static std::vector<std::string> tomorrowPattern;
        // a week
        static std::vector<std::string> singularPattern;
        // in 10 days
        static std::vector<std::string> dayDescriptionPattern;
        // in 2 weeks
        static std::vector<std::string> weekDescriptionPattern;
        // in a month (will add 30 days per month)
        static std::vector<std::string> monthDescriptionPattern;

        static std::vector<std::string> yearDescriptionPattern;

        static std::vector<std::string> hourDescriptionPattern;

        static std::vector<std::string> minDescriptionPattern;

        // next week
        static std::vector<std::string> nextPattern;

        static std::string AM;
        static std::string PM;
        static std::string timeDivider;
    };
}
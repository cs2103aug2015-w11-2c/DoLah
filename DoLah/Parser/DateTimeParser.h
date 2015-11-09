#pragma once

/**
 * @class DateTimeParser.h Parser/DateTimeParser.h
 * @brief Static library to handle conversion from string vector to std::tm.
 *
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

        /**
         * Handles dates such as Monday
         * @param[in]   date Expressed in int value as the std::tm
         * @param[in]   notThisWeek True if the date is not this week
         * @return The number of days difference compared to the current day.
         */
        static int getDateModifier(int, bool);
        
        /**
         * Deals with the expressions that describe relative date.
         * e.x. today, tomorrow, 10 days, 1 week, next Thursday...
         * @param[in]   strArr The string vector list to be evaluated.
         * @param[in]   lowerBound Returned day is above this lowerbound.
         * @return The number of seconds difference compared to the current time.
         */
        static int checkDateModifier(std::vector<std::string>, std::tm);

        /**
         * Deals with the expressions that describe relative time.
         * e.x. next hour, 30 minutes...
         * @param[in]   strArr The string vector list to be evaluated.
         * @return The number of seconds difference compared to the current time.
         */
        static int checkTimeModifier(std::vector<std::string>);

        /**
         * Check the specific date format in DMY and MDY format
         * e.x. 25 December 2015
         * @param[in]   strArr The string vector list to be evaluated.
         * @return Date in std::tm format.
         */
        static std::tm classifyDate(std::vector<std::string>);

        /**
         * Check Day Month Year format and convert it into date format
         * @param[in]   strArr The string vector list to be evaluated.
         * @return Date in std::tm format.
         */
        static std::tm checkDMYformat(std::vector<std::string>);
        
        /**
         * Check Month Day Year format and convert it into date format
         * @param[in]   strArr The string vector list to be evaluated.
         * @return Date in std::tm format.
         */
        static std::tm checkMDYformat(std::vector<std::string>);
    private:
        static int REJECT; /// Arbitrary int value to indicates REJECT in any classification.
        static std::string CENTURY; /// For year described in 2 digits, 20 will be added. e.x. 15 -> 2015
        static int MIN_IN_SECS; /// Minute in Seconds
        static int HOUR_IN_SECS;  /// Hour in Seconds
        static int DAY_IN_SECS;  /// Day in Seconds
        static int WEEK_IN_SECS;  /// Week in Seconds
        static int MONTH_IN_SECS;  /// Month in Seconds
        static int DEFAULT_TIME; /// If time is not specified, 23:59 is the default time.

        static std::vector<std::string> DATE_PATTERN; /// Monday, Mon
        static std::vector<std::string> MONTH_PATTERN; /// 12, December, Dec

        static std::string DAY_APPENDIX_PATTERN; /// 1st, 2nd, 3rd, 4th
        static std::vector<std::string> DECORATORS; /// 25th of Dec
        static std::vector<std::string> PUNCTUATIONS; /// Sunday, 17th of March
        static std::vector<std::string> DATE_DIVIDERS; /// 25.12.2015, 25/12/2015, 25-12-2015

        static std::vector<std::string> TODAY_INDICATORS; /// today
        static std::vector<std::string> TOMORROW_INDICATORS; /// tomorrow
        static std::vector<std::string> SINGULAR_FORMATS; /// a, an, the, one
        static std::vector<std::string> DAY_DESCRIPTION_INDICATOR; /// 10 days
        static std::vector<std::string> WEEK_DESCRIPTION_INDICATOR; /// 2 weeks
        static std::vector<std::string> MONTH_DESCRIPTION_INDICATOR; /// 3 months
        static std::vector<std::string> YEAR_DESCRIPTION_INDICATOR; /// 4 year
        static std::vector<std::string> HOUR_DESCRIPTION_INDICATOR; /// 3 hours
        static std::vector<std::string> MIN_DESCRIPTION_INDICATOR; /// 30 mins
        static std::vector<std::string> NEXT_FORMATS; /// next, coming

        static std::string AM; /// am
        static std::string PM; /// pm
        static std::string TIME_DIVIDERS; /// 12:30
    };
}
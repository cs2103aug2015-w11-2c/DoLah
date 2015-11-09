#include <string>
#include <vector>

/**
 * @class TaskTokenizer.h Parser/TaskTokenizer.h
 * @brief Tokenize the string vector list into tokens that make up Task object.
 */

#include "ParserLibrary.h"
#include "DateTimeParser.h"

#pragma once
namespace DoLah {
    class TaskTokenizer {
    public:
        TaskTokenizer();
        ~TaskTokenizer();

        /**
         * Find the date from the string vector list and returns it as well as removing the date portion from the referenced list.
         * @param[in, out]  lineArr Reference of a string vector list to be evaluated. Date portion will be removed.
         * @return Date found in std::tm format.
         */
        static std::vector<std::tm> findAndRemoveDate(std::vector<std::string>&);

        /**
         * Find the description from the string vector list.
         * @param[in]   lineArr String vector list to be evaluated.
         * @return String that represents the description.
         */
        static std::string findDescription(std::vector<std::string>);

        /**
         * Find the tags from the string vector list.
         * @param[in]   lineArr String vector list to be evaluated.
         * @return String vector list of tags.
         */
        static std::vector<std::string> findTags(std::vector<std::string>);
        
    private:
        static std::vector<std::string> DEADLINE_INDICATOR;
        static std::vector<std::string> EVENT_INDICATOR;
        static std::vector<std::string> EVENT_SEPARATOR;
        static std::string SCHEDULE_INDICATOR;
        static std::vector<std::string> SCHEDULE_SEPARATOR;
        static std::string TAG_INDICATOR;
        static int DEFAULTTMYEAR;
        
        /**
         * Find all dates from the given string vector list.
         * @param[in]   lineArr String vector list to be evaluated.
         * @return Vector list of time in std::tm format.
         */
        static std::vector<std::tm> TaskTokenizer::findDate(std::vector<std::string>);

        /**
         * Find date for deadline task.
         * @param[in]   lineArr String vector list to be evaluated.
         * @return Vector list of time in std::tm format.
         */
        static std::vector<std::tm> TaskTokenizer::findDeadline(std::vector<std::string>);

        /**
         * Find dates for event task.
         * @param[in]   lineArr String vector list to be evaluated.
         * @return Vector list of time in std::tm format.
         */
        static std::vector<std::tm> TaskTokenizer::findEvent(std::vector<std::string>, std::vector<std::string>);
    };
}
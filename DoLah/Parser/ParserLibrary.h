//@@collate A0116722M
#pragma once

#include <string>
#include <vector>
#include <algorithm>

namespace DoLah {

    /**
    * @class ParserLibrary ParserLibrary.h Parser/ParserLibrary.h
    * @brief A library consists of general functions.
    *
    * These functions are widly used in parse component.
    */
    class ParserLibrary {
    public:
        ParserLibrary();
        ~ParserLibrary();

        /**
         * Equivalent to strip of Java. Remove empty spaces before and after the string.
         * @param[in]   str String to be cleaned
         * return Clean string
         */
        static std::string strip(std::string);

        /**
         * Equivalent to explode of PHP or split of Java. Split string on each delimeters.
         * @param[in]   line String to be split
         * return Vector list of substring
         */
        static std::vector<std::string> explode(std::string, std::string);
        
        /**
         * Equivalent to implode of PHP or merge of Java. Put elements together with delimeter between.
         * @param[in]   line String vector list to be merged
         * return Merged string
         */
        static std::string implode(std::vector<std::string>, std::string);

        /**
         * Implode string vector list with an empty space.
         * @param[in]   vec String vector list to be converted.
         * return Merged string
         */
        static std::string vectorToString(std::vector<std::string> vec);

        /**
         * Make all the alphabets in the string into lowercase.
         * @param[in]   str String to be converted.
         * return String with all alphabet in lowercase.
         */
        static std::string tolowercase(std::string str);

        /**
         * Check whether the given string vector list contains the string or not.
         * @param[in]   arr String vector list
         * @param[in]   str String to be found
         * return True if it is in the list.
         */
        static bool inStringArray(std::vector<std::string> arr, std::string str);

        /**
         * Get the index of the element in the list.
         * @param[in]   arr String vector list
         * @param[in]   str String to be found
         * return Index of the element. If there is no such element, returns std::npos.
         */
        static size_t ParserLibrary::getIndexInStringArray(std::vector<std::string>, std::string);

        /**
         * Clean up duplicates from the string vector list.
         * @param[in]   vector String vector list to be cleaned.
         * return Stirng vector list with unique elements.
         */
        static std::vector<std::string> stringVectorUnique(std::vector<std::string> vector);

        /**
         * Check whether that string is a decimal integer or not.
         * @param[in]   str String to be checked.
         * return True if it is a decimal integer.
         */
        static bool isDecimal(std::string str);

        /**
         * Remove the first occurance of the substring from the string.
         * @param[in]   str Original string.
         * @param[in]   substr Substring to be removed.
         * return Pruned string.
         */
        static std::string stringRemove(std::string str, std::string substr);

        /**
         * Remove the all occurances of the substring from the string.
         * @param[in]   str Original string.
         * @param[in]   substr Substring to be removed.
         * return Pruned string.
         */
        static std::string stringRemoveAll(std::string str, std::string substr);

        /**
         * Removes the double spacing repeatedly until there is only single spacing.
         * @param[in]   str String to be cleaned up.
         * @return Clean string
         */
        static std::string removeDoubleSpacing(std::string);

        /**
         * Removes the elements of the list 
         * @param[in]   origin String vector list to be cleaned.
         * @param[in]   list List of string vector list that needs to be cleaned from the origin.
         * @return Clean string vector list.
         */
        static std::vector<std::string> removeElementsFromStringVector(std::vector<std::string>, std::vector<std::string>);
    };

}
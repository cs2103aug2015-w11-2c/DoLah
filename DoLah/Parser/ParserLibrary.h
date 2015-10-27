#pragma once

#include <string>
#include <vector>
#include <algorithm>

namespace DoLah {

    class ParserLibrary {
    public:
        ParserLibrary();
        ~ParserLibrary();

        static std::string strip(std::string);
        static std::vector<std::string> explode(std::string line, std::string delimeter);
        static std::string implode(std::vector<std::string> line, std::string delimeter);
        static std::string vectorToString(std::vector<std::string> vec);
        static std::string tolowercase(std::string str);
        static bool inStringArray(std::vector<std::string> arr, std::string str);
        static size_t ParserLibrary::getIndexInStringArray(std::vector<std::string>, std::string);
        static std::vector<std::string> stringVectorUnique(std::vector<std::string> vector);
        static bool isDecimal(std::string str);
        static std::string stringRemove(std::string str, std::string substr);
        static std::vector<std::string> removeElementsFromStringVector(std::vector<std::string>, std::vector<std::string>);
    };

}
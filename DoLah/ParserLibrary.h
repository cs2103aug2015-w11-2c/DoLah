#pragma once

#include <string>
#include <vector>
#include <algorithm>

class ParserLibrary {
public:
    ParserLibrary();
    ~ParserLibrary();

    static std::vector<std::string> explode(std::string line, std::string delimeter);
    static std::string implode(std::vector<std::string> line, std::string delimeter);
    static std::string vectorToString(std::vector<std::string> vec);
    static std::string tolowercase(std::string str);
    static bool inArray(std::vector<std::string> arr, std::string str);
    static std::vector<std::string> stringVectorUnique(std::vector<std::string> vector);
};

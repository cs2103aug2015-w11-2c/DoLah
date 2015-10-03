#pragma once

#include <string>
#include <vector>
#include <algorithm>

class ParserLibrary {
public:
    ParserLibrary();
    ~ParserLibrary();

    static std::vector<std::string> explode(const std::string &, const std::string &);
    static std::string implode(std::vector<std::string> line, const std::string &);
    static std::string vectorToString(std::vector<std::string> vec);
    static std::string tolowercase(const std::string &);
    static bool inArray(std::vector<std::string> arr, const std::string &);
    static std::vector<std::string> stringVectorUnique(std::vector<std::string> vector);
};


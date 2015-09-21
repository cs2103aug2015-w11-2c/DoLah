#pragma once

#include <string>
#include <vector>

class TokenizerLibrary {
public:
    TokenizerLibrary();
    ~TokenizerLibrary();

    static std::vector<std::string> explode(std::string line);
    static std::string vectorToString(std::vector<std::string> vec);

};


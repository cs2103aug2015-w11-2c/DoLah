#pragma once

#include <string>
#include <vector>

class CommandTokenizer {
public:
    CommandTokenizer();
    ~CommandTokenizer();

    std::vector<std::string> tokenize(std::string line);
    
private:
};


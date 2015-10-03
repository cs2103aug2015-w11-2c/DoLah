#include "ParserLibrary.h"



ParserLibrary::ParserLibrary() {
}


ParserLibrary::~ParserLibrary() {
}


std::vector<std::string> ParserLibrary::explode(std::string line, std::string delimeter) {
    std::vector<std::string> out;
    int from = 0;
    int to;

    while ((to = line.find(delimeter, from)) != -1) {
        out.push_back(line.substr(from, to - from));
        from = to + 1;
    }
    out.push_back(line.substr(from, line.size() - from));

    return out;
}

std::string ParserLibrary::implode(std::vector<std::string> line, std::string delimeter) {
    std::string out = "";

    for (size_t i = 0; i < line.size(); i++) {
        if (i > 0) {
            out += delimeter;
        }
        out += line.at(i);
    }

    return out;

}


std::string ParserLibrary::vectorToString(std::vector<std::string> vec) {
    std::string str = "{ ";
    for (int i = 0; i < (int)vec.size(); i++) {
        str += vec.at(i);
        if (i < (int)vec.size() - 1) {
            str += +", ";
        }
    }
    str += " }";
    return str;
}

std::string ParserLibrary::tolowercase(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

bool ParserLibrary::inArray(std::vector<std::string> arr, std::string str) {
    return std::find(arr.begin(), arr.end(), ParserLibrary::tolowercase(str)) != arr.end();
}

std::vector<std::string> ParserLibrary::stringVectorUnique(std::vector<std::string> vector) {
    std::vector<std::string>::iterator it;
    it = std::unique(vector.begin(), vector.end());
    vector.resize(std::distance(vector.begin(), it));
    return vector;
}
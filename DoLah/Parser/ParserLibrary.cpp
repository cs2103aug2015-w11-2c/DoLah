#include "ParserLibrary.h"

namespace DoLah {

    ParserLibrary::ParserLibrary() {
    }


    ParserLibrary::~ParserLibrary() {
    }


    std::string ParserLibrary::strip(std::string str) {
        if (str.length() == 0) return str;

        std::string out = str;
        size_t from = 0;
        for (; from < out.length() && out.at(from) == ' '; from++) {
        }

        size_t to = out.length() - 1;
        for (; to > from && out.at(to) == ' '; to--) {
        }

        out = out.substr(from, to - from + 1);
        return out;
    }


    std::vector<std::string> ParserLibrary::explode(std::string input, std::string delimeter) {
        std::string line = strip(input);
        if (line.length() == 0) {
            return {};
        }

        std::vector<std::string> out;
        size_t from = 0;
        size_t to;

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

    bool ParserLibrary::inStringArray(std::vector<std::string> arr, std::string str) {
        return std::find(arr.begin(), arr.end(), ParserLibrary::tolowercase(str)) != arr.end();
    }

    std::vector<std::string> ParserLibrary::stringVectorUnique(std::vector<std::string> vector) {
        std::vector<std::string>::iterator it;
        it = std::unique(vector.begin(), vector.end());
        vector.resize(std::distance(vector.begin(), it));
        return vector;
    }


    bool ParserLibrary::isDecimal(std::string str) {
        for (size_t i = 0; i < str.length(); i++) {
            if (str.at(i) > '9' || str.at(i) < '0') {
                return false;
            }
        }
        return true;
    }


    std::string ParserLibrary::stringRemove(std::string str, std::string substr) {
        size_t f = str.find(substr);
        str.replace(f, substr.length(), "");
        return str;
    }

    std::vector<std::string> ParserLibrary::removeElementsFromStringVector(std::vector<std::string> origin, std::vector<std::string> list) {
        for (size_t i = 0; i < origin.size(); i++) {
            for (size_t j = 0; j < list.size(); j++) {
                if (tolowercase(origin.at(i)) == tolowercase(list.at(j))) {
                    origin.erase(origin.begin() + i);
                }
            }
        }
        return origin;
    }

}
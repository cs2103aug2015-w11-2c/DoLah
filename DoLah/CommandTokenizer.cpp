#include "CommandTokenizer.h"

namespace DoLah {

    std::vector<std::string> CommandTokenizer::commandList = { "add", "display", "undo", "delete", "edit", "clear", "search", "sort" };
    std::vector<std::string> CommandTokenizer::timeSubCommandList = { "on" };

    std::string CommandTokenizer::tag = "#";

    CommandTokenizer::CommandTokenizer() {
    }


    CommandTokenizer::~CommandTokenizer() {
    }

    std::string CommandTokenizer::findCommand(std::vector<std::string> lineArr) {
        return lineArr.at(0);   
    }

    std::vector<std::string> CommandTokenizer::findTags(std::vector<std::string> lineArr) {
        std::vector<std::string> tags;
        std::vector<std::string> moretags;

        for (size_t i = 0; i < lineArr.size(); i++) {
            moretags = ParserLibrary::explode(lineArr.at(i), tag);
            tags.insert(tags.begin(), moretags.begin() + 1, moretags.end());
        }

        for (size_t i = 0; i < tags.size(); i++) {
            tags.at(i) = ParserLibrary::tolowercase(tags.at(i));
        }

        tags = ParserLibrary::stringVectorUnique(tags);

        return tags;
    }

    std::string CommandTokenizer::findDescription(std::vector<std::string> lineArr) {
        std::string output;

        std::vector<std::string> description(lineArr.begin() + 1, lineArr.end());
        output = ParserLibrary::implode(description, " ");

        return output;
    }

    std::vector<std::tm> CommandTokenizer::findDate(std::vector<std::string> lineArr) {
        CommandTokenizer ct;

        std::vector<std::string> timeSubCommandList = { "on" };

        std::vector<std::tm> output;

        bool dateFlag = false;
        for (size_t i = lineArr.size() - 1; i > 0; i--) {
            if (ParserLibrary::inStringArray(timeSubCommandList, lineArr.at(i))) {
                dateFlag = true;
            }
            if (dateFlag) {
                std::vector<std::string> subVec(lineArr.begin() + i + 1, lineArr.end());
                try {
                    output.push_back(DateTimeParser::toDateFormat(subVec));
                } catch (std::invalid_argument e) {
                    throw std::invalid_argument("");
                }
            }
            dateFlag = false;
        }
        if (output.size() == 0) {
            throw std::invalid_argument("");
        }

        return output;
    }

    int CommandTokenizer::findTaskID(std::vector<std::string>) {


        return 0;
    }

}

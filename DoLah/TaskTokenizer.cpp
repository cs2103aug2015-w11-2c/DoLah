#include "TaskTokenizer.h"


namespace DoLah {

    std::vector<std::string> TaskTokenizer::timeSubCommandList = { "on" };
    std::string TaskTokenizer::tag = "#";

    TaskTokenizer::TaskTokenizer() {
    }


    TaskTokenizer::~TaskTokenizer() {
    }

    std::vector<std::string> TaskTokenizer::findTags(std::vector<std::string> lineArr) {
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

    std::string TaskTokenizer::findDescription(std::vector<std::string> lineArr) {
        return ParserLibrary::implode(lineArr, " ");
    }

    std::vector<std::tm> TaskTokenizer::findDate(std::vector<std::string> &lineArr) {
        TaskTokenizer ct;
        std::vector<std::tm> output;

        bool dateFlag = false;
        for (size_t i = lineArr.size() - 1; i > 0; i--) {
            if (ParserLibrary::inStringArray(timeSubCommandList, lineArr.at(i))) {
                dateFlag = true;
            }
            if (dateFlag) {
                std::vector<std::string> subVec(lineArr.begin() + i + 1, lineArr.end());
                try {
                    std::tm time = DateTimeParser::toDateFormat(subVec);
                    output.push_back(time);
                    lineArr.erase(lineArr.begin() + i, lineArr.end());
                } catch (std::invalid_argument e) {
                    // Don't recognize it as date and ignore
                }
            }
            dateFlag = false;
        }

        return output;
    }
}

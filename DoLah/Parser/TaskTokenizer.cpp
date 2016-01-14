//@@author A0116722M
#include "TaskTokenizer.h"


namespace DoLah {
    std::vector<std::string> TaskTokenizer::EVENT_INDICATOR = { "in", "on", "from", "between" };
    std::vector<std::string> TaskTokenizer::DEADLINE_INDICATOR = { "in", "on", "by", "due", "at" };
    std::vector<std::string> TaskTokenizer::EVENT_SEPARATOR = { "to", "~", "until" };
    std::string TaskTokenizer::TAG_INDICATOR = "#";
    int TaskTokenizer::DEFAULTTMYEAR = 0; // represents 1900

    TaskTokenizer::TaskTokenizer() {
    }


    TaskTokenizer::~TaskTokenizer() {
    }

    std::vector<std::string> TaskTokenizer::findTags(std::vector<std::string> lineArr) {
        std::vector<std::string> tags;
        std::vector<std::string> moretags;

        for (size_t i = 0; i < lineArr.size(); i++) {
            moretags = ParserLibrary::explode(lineArr.at(i), TAG_INDICATOR);
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

    std::vector<std::tm> TaskTokenizer::findDeadline(std::vector<std::string> subVec) {
        std::tm current = TimeManager::getCurrentTime();
        std::tm dueDate;

        dueDate = DateTimeParser::toDateFormat(subVec);

        return { dueDate };
    }

    std::vector<std::tm> TaskTokenizer::findEvent(std::vector<std::string> startDateArr, std::vector<std::string> endDateArr) {
        std::tm current = TimeManager::getCurrentTime();
        std::tm startdate = DateTimeParser::toDateFormat(startDateArr);
        std::tm enddate = DateTimeParser::toDateFormat(endDateArr, startdate);

        if (startdate.tm_year == DEFAULTTMYEAR && startdate.tm_year == DEFAULTTMYEAR) {
            TimeManager::copyDay(current, startdate);
            TimeManager::copyDay(current, enddate);
            if (TimeManager::compareTime(startdate, enddate) < 0) {
                enddate.tm_mon += 1;
                mktime(&enddate);
            }
        } else if (startdate.tm_year == DEFAULTTMYEAR) {
            TimeManager::copyDay(enddate, startdate);
            if (TimeManager::compareTime(startdate, enddate) < 0) {
                throw std::invalid_argument("");
            }
        } else if (enddate.tm_year == DEFAULTTMYEAR) {
            TimeManager::copyDay(startdate, enddate);
            if (TimeManager::compareTime(startdate, enddate) < 0) {
                enddate.tm_mon += 1;
                mktime(&enddate);
            }
        }

        // time cannot backflow!
        if (TimeManager::compareTime(startdate, enddate) < 0) {
            throw std::invalid_argument("");
        }

        return { startdate, enddate };
    }

    std::vector<std::tm> TaskTokenizer::findDate(std::vector<std::string> lineArr) {
        int index = 0;
        std::vector<std::tm> output;

        if (ParserLibrary::inStringArray(EVENT_INDICATOR, ParserLibrary::tolowercase(lineArr.at(index)))) {
            size_t indicatorIndex = ParserLibrary::getIndexInStringArray(EVENT_INDICATOR, ParserLibrary::tolowercase(lineArr.at(index)));
            std::vector<std::string> subVec(lineArr.begin() + index + 1, lineArr.end());
            for (size_t j = 0; j < subVec.size(); j++) {
                if (ParserLibrary::inStringArray(EVENT_SEPARATOR, ParserLibrary::tolowercase(subVec.at(j)))) {
                    std::vector<std::string> startDateArr(subVec.begin(), subVec.begin() + j);
                    std::vector<std::string> endDateArr(subVec.begin() + j + 1, subVec.end());

                    output = findEvent(startDateArr, endDateArr);
                    break;
                }
            }
        }

        if (output.size() == 0 && ParserLibrary::inStringArray(DEADLINE_INDICATOR, ParserLibrary::tolowercase(lineArr.at(index)))) {
            std::vector<std::string> subVec(lineArr.begin() + index + 1, lineArr.end());

            output = findDeadline(subVec);
        }

        if (output.size() == 0) {
            throw std::invalid_argument("");
        }

        return output;
    }

    std::vector<std::tm> TaskTokenizer::findAndRemoveDate(std::vector<std::string> &lineArr) {
        std::tm current = TimeManager::getCurrentTime();
        std::vector<std::tm> output;

        std::vector<std::string> prunedArr = lineArr;

        for (size_t index = 0; index < lineArr.size(); index++) {
            try {
                std::vector<std::string> subVec(lineArr.begin() + index, lineArr.end());
                output = findDate(subVec);
                prunedArr = std::vector<std::string>(lineArr.begin(), lineArr.begin() + index);
            } catch (std::invalid_argument e) {
                // continue
            }
        }

        lineArr = prunedArr;
        return output;
    }
}

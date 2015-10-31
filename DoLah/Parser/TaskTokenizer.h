#include <string>
#include <vector>

#include "ParserLibrary.h"
#include "DateTimeParser.h"

#pragma once
namespace DoLah {
    class TaskTokenizer {
    public:
        TaskTokenizer();
        ~TaskTokenizer();

        // Fixed format ~ date is at the end of command indicated by subcommand 'on'.
        // It will prune the date part from the input
        static std::vector<std::tm> findAndRemoveDate(std::vector<std::string>&);

        // The input should not have date already, and thus findDate always come before this.
        // Tag is ignored and the hashes remain in description.
        static std::string findDescription(std::vector<std::string>);

        // A tag is indicated by hash (#)
        static std::vector<std::string> findTags(std::vector<std::string>);
        
    private:
        static std::vector<std::string> DEADLINE_INDICATOR;
        static std::vector<std::string> EVENT_INDICATOR;
        static std::vector<std::string> EVENT_SEPARATOR;
        static std::string SCHEDULE_INDICATOR;
        static std::vector<std::string> SCHEDULE_SEPARATOR;
        static std::string tag;
        static int defaultTMYear;
        
        static std::vector<std::tm> TaskTokenizer::findDate(std::vector<std::string>, int);
        static std::vector<std::tm> TaskTokenizer::findDeadline(std::vector<std::string>);
        static std::vector<std::tm> TaskTokenizer::findEvent(std::vector<std::string>, std::vector<std::string>);
    };
}
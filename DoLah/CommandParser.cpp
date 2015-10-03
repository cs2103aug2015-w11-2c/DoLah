#include "CommandParser.h"



CommandParser::CommandParser() {
}


CommandParser::~CommandParser() {
}

void CommandParser::parse(const std::string &line) {
    CommandTokenizer tokenizer;
    std::vector<std::string> lineArr = ParserLibrary::explode(line, " ");

    std::string command = tokenizer.findCommand(lineArr);

    if (command == "add") {
        std::string description = tokenizer.findDescription(lineArr);
        std::vector<std::string> tags = tokenizer.findTags(lineArr);
        int priority = tokenizer.findPriority(lineArr);
    }
}
#include "CommandParser.h"



CommandParser::CommandParser() {
}


CommandParser::~CommandParser() {
}

void CommandParser::parse(const std::string &line) {
    CommandTokenizer tokenizer;
    std::vector<std::string> lineArr = ParserLibrary::explode(line, " ");

    std::vector<std::string> commands = tokenizer.findCommand(lineArr);

    if (1==1) {

    }
}
#include "CommandTokenizer.h"

namespace DoLah {

    std::vector<std::string> CommandTokenizer::commandList = { "add", "display", "undo", "delete", "edit", "clear", "search", "sort" };

    CommandTokenizer::CommandTokenizer() {
    }

    CommandTokenizer::~CommandTokenizer() {
    }

    std::string CommandTokenizer::findCommand(std::vector<std::string> &lineArr) {
        std::string command = lineArr.at(0);
        if (!ParserLibrary::inStringArray(commandList, command)) {
            return std::string();
        }
        lineArr.erase(lineArr.begin());
        return command;
    }
}

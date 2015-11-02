#include "CommandTokenizer.h"

namespace DoLah {

    std::vector<std::string> CommandTokenizer::commandList = { "add", "undone", "done", "display", "undo", "delete", "del", "edit", "clear", "search", "sort", "redo" };

    CommandTokenizer::CommandTokenizer() {
    }

    CommandTokenizer::~CommandTokenizer() {
    }

    std::string CommandTokenizer::findCommand(std::vector<std::string> &lineArr) {
        std::string command = lineArr.at(0);
        if (!ParserLibrary::inStringArray(commandList, command)) {
            return std::string();
        }

        return command;
    }

    std::vector<std::string> CommandTokenizer::pruneCommand(std::vector<std::string> lineArr) {
        lineArr.erase(lineArr.begin());
        return lineArr;
    }
}

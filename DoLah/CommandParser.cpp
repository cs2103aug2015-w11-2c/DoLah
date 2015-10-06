#include "CommandParser.h"

namespace DoLah {
    std::string CommandParser::ADD = "add";
    std::string CommandParser::SEARCH = "search";
    std::string CommandParser::EDIT = "edit";
    std::string CommandParser::DELETE = "delete";
    std::string CommandParser::CLEAR = "clear";
    std::string CommandParser::UNDO = "undo";

    std::string CommandParser::UNKNOWN_COMMAND_MESSAGE = "command not recognized";
    std::string CommandParser::TOO_MANY_ARGUMENTS_MESSAGE = "Too many arguments";
    std::string CommandParser::TOO_LITTLE_ARGUMENTS_MESSAGE = "Too little arguments";


    CommandParser::CommandParser() {
    }


    CommandParser::~CommandParser() {
    }


    AddTaskCommand CommandParser::parseAdd(std::vector<std::string> inputArr) {
        std::vector<std::tm> dueDate = CommandTokenizer::findDate(inputArr);
        std::vector<std::string> tags = CommandTokenizer::findTags(inputArr);
        std::string description = CommandTokenizer::findDescription(inputArr);

        if (dueDate.size() == 0) {
            // FloatingTask
            FloatingTask task;
            task.setName(description);
            
            Calendar cal;
            AddTaskCommand command(&task);
            return command;
        } else if (dueDate.size() == 1) {
            // DeadlineTask
            DeadlineTask task;
            task.setName(description);
            //task.setDueDate(dueDate);
        } else if (dueDate.size() == 2) {
            // EventTask !to be implemented later
        }
    }


    SearchTaskCommand CommandParser::parseSearch(std::vector<std::string> inputArr) {
        std::vector<std::string> subVec(inputArr.begin() + 1, inputArr.end());
        std::string arg = ParserLibrary::implode(subVec, " ");
        SearchTaskCommand command(arg);
        return command;
    }


    EditTaskCommand CommandParser::parseEdit(std::vector<std::string> inputArr) {
        int arg = std::stoi(inputArr.at(1));

    }


    DeleteTaskCommand CommandParser::parseDelete(std::vector<std::string> inputArr) {
        int arg = std::stoi(inputArr.at(1));
        DeleteTaskCommand command(arg);
        return command;
    }


    ClearTaskCommand CommandParser::parseClear() {
        ClearTaskCommand command;
        return command;
    }


    UndoTaskCommand CommandParser::parseUndo() {
        UndoTaskCommand command;
        return command;
    }


    ITaskCommand* CommandParser::parse(std::string input) {
        std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");
        std::string command = DoLah::CommandTokenizer::findCommand(inputArr);
        if (command == ADD) {
            if (inputArr.size() == 1) {
                throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
            }
            return &parseAdd(inputArr);
        } else if (command == SEARCH) {
            if (inputArr.size() == 1) {
                throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
            }
            return &parseSearch(inputArr);
        } else if (command == EDIT) {
            if (inputArr.size() == 1) {
                throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
            } else if (inputArr.size() > 2) {
                throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
            }
            return &parseEdit(inputArr);
        } else if (command == DELETE) {
            if (inputArr.size() == 1) {
                throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
            } else if (inputArr.size() > 2) {
                throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
            }
            return &parseDelete(inputArr);
        } else if (command == CLEAR) {
            if (inputArr.size() > 1) {
                throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
            }
            return &parseClear();
        } else if (command == UNDO) {
            if (inputArr.size() > 1) {
                throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
            }
            return &parseUndo();
        } else {
            throw std::invalid_argument(UNKNOWN_COMMAND_MESSAGE);
        }
    }
}


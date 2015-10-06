#include "CommandParser.h"

namespace DoLah {
    std::string CommandParser::ADD = "add";
    std::string CommandParser::SEARCH = "search";
    std::string CommandParser::EDIT = "edit";
    std::string CommandParser::DELETE = "delete";
    std::string CommandParser::CLEAR = "clear";
    std::string CommandParser::UNDO = "undo";

    std::string CommandParser::TOO_MANY_ARGUMENTS_MESSAGE = "Too many arguments";
    std::string CommandParser::TOO_LITTLE_ARGUMENTS_MESSAGE = "Too little arguments";


    CommandParser::CommandParser() {
    }


    CommandParser::~CommandParser() {
    }


    void CommandParser::parseAdd(std::vector<std::string> inputArr) {
        std::vector<std::tm> dueDate = CommandTokenizer::findDate(inputArr);
        std::vector<std::string> tags = CommandTokenizer::findTags(inputArr);
        std::string description = CommandTokenizer::findDescription(inputArr);

        if (dueDate.size() == 0) {
            // FloatingTask
            FloatingTask task;
            task.setName(description);
        } else if (dueDate.size() == 1) {
            // DeadlineTask
            DeadlineTask task;
            task.setName(description);
            //task.setDueDate(dueDate);
        } else if (dueDate.size() == 2) {
            // EventTask !to be implemented later
        }

        // create Command
    }


    void CommandParser::parseSearch(std::string input) {
        int pos = input.find(" ");
        std::string arg = input.substr(pos, input.size() - pos);

        //make ITaskCommand
    }


    void CommandParser::parseEdit(std::vector<std::string> inputArr) {
        int arg = std::stoi(inputArr.at(1));

        //make ITaskCommand
    }


    void CommandParser::parseDelete(std::vector<std::string> inputArr) {
        int arg = std::stoi(inputArr.at(1));

        //make ITaskCommand
    }


    void CommandParser::parseClear() {
        //make ITaskCommand
    }


    void CommandParser::parseUndo() {
        //make ITaskCommand
    }


    void CommandParser::parse(std::string input) {
        std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");
        std::string command = DoLah::CommandTokenizer::findCommand(inputArr);
        if (command == ADD) {
            if (inputArr.size() == 1) {
                throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
            }
            parseAdd(inputArr);
        } else if (command == SEARCH) {
            if (inputArr.size() == 1) {
                throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
            }
            parseSearch(input);
        } else if (command == EDIT) {
            if (inputArr.size() == 1) {
                throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
            } else if (inputArr.size() > 2) {
                throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
            }
        } else if (command == DELETE) {
            if (inputArr.size() == 1) {
                throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
            } else if (inputArr.size() > 2) {
                throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
            }
        } else if (command == CLEAR) {
            if (inputArr.size() > 1) {
                throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
            }
        } else if (command == UNDO) {
            if (inputArr.size() > 1) {
                throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
            }
        }
    }
}


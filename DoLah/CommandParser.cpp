#include "CommandParser.h"

namespace DoLah {
    std::string CommandParser::ADD = "add";
    std::string CommandParser::SEARCH = "search";
    std::string CommandParser::EDIT = "edit";
    std::string CommandParser::DELETE = "delete";
    std::string CommandParser::CLEAR = "clear";
    std::string CommandParser::UNDO = "undo";

    std::string CommandParser::UNHANDLED_COMMAND_MESSAGE = "Command not handled";
    std::string CommandParser::UNKNOWN_COMMAND_MESSAGE = "Command not recognized";
    std::string CommandParser::TOO_MANY_ARGUMENTS_MESSAGE = "Too many arguments";
    std::string CommandParser::TOO_LITTLE_ARGUMENTS_MESSAGE = "Too little arguments";
    std::string CommandParser::INVALID_TASK_ID_ARGUMENT = "Invalid edit argument";


    CommandParser::CommandParser() {
    }


    CommandParser::~CommandParser() {
    }

    AddTaskCommand CommandParser::parseAdd(std::vector<std::string> inputArr) {
        if (inputArr.size() == 0) {
            throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
        }

        AbstractTask* task = TaskParser::parseTask(inputArr);
        return AddTaskCommand(task);
    }


    SearchTaskCommand CommandParser::parseSearch(std::vector<std::string> inputArr) {
        if (inputArr.size() == 0) {
            throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
        }

        std::string arg = ParserLibrary::implode(inputArr, " ");
        return SearchTaskCommand(arg);
    }


    EditTaskCommand CommandParser::parseEdit(std::vector<std::string> inputArr) {
        if (inputArr.size() == 0) {
            throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
        }

        int taskID;
        try {
            taskID = std::stoi(inputArr.at(0));
        } catch (std::invalid_argument e) {
            throw std::invalid_argument(INVALID_TASK_ID_ARGUMENT);
        }

        std::vector<std::string> subVec(inputArr.begin() + 1, inputArr.end());
        AbstractTask* task = TaskParser::parseTask(subVec);
        return EditTaskCommand(taskID, task);
    }


    DeleteTaskCommand CommandParser::parseDelete(std::vector<std::string> inputArr) {
        if (inputArr.size() == 0) {
            throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
        } else if (inputArr.size() > 1) {
            throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
        }

        int taskID;
        try {
            taskID = std::stoi(inputArr.at(0));
        } catch (std::invalid_argument e) {
            throw std::invalid_argument(INVALID_TASK_ID_ARGUMENT);
        }
        return DeleteTaskCommand(taskID);
    }


    ClearTaskCommand CommandParser::parseClear(std::vector<std::string> inputArr) {
        if (inputArr.size() > 0) {
            throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
        }

        ClearTaskCommand command;
        return command;
    }


    UndoTaskCommand CommandParser::parseUndo(std::vector<std::string> inputArr) {
        if (inputArr.size() > 0) {
            throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
        }

        UndoTaskCommand command;
        return command;
    }


    ITaskCommand* CommandParser::parse(std::string input) {
        std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");
        std::string command = DoLah::CommandTokenizer::findCommand(inputArr);

        if (command.empty()) {
            throw std::invalid_argument(UNKNOWN_COMMAND_MESSAGE);
        }

        if (command == ADD) {
            AddTaskCommand* command = new AddTaskCommand(parseAdd(inputArr));
            return command;
        } else if (command == SEARCH) {
            SearchTaskCommand* command = new SearchTaskCommand(parseSearch(inputArr));
            return command;
        } else if (command == EDIT) {
            EditTaskCommand* command = new EditTaskCommand(parseEdit(inputArr));
            return command;
        } else if (command == DELETE) {
            DeleteTaskCommand* command = new DeleteTaskCommand(parseDelete(inputArr));
            return command;
        } else if (command == CLEAR) {
            ClearTaskCommand* command = new ClearTaskCommand(parseClear(inputArr));
            return command;
        } else if (command == UNDO) {
            UndoTaskCommand* command = new UndoTaskCommand(parseUndo(inputArr));
            return command;
        } else {
            throw std::invalid_argument(UNHANDLED_COMMAND_MESSAGE);
        }
    }
}


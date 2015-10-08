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

    
    AbstractTask* CommandParser::parseTask(std::vector<std::string> inputArr) {
        std::vector<std::tm> dates = CommandTokenizer::findDate(inputArr);
        std::vector<std::string> tags = CommandTokenizer::findTags(inputArr);
        std::string description = CommandTokenizer::findDescription(inputArr);

        if (dates.size() == 1) {
            DeadlineTask* task = new DeadlineTask();
            task->setName(description);
            task->setTags(tags);
            task->setDueDate(dates.at(0));
            return task;
        } else if (dates.size() == 2) {
            EventTask* task = new EventTask();
            task->setName(description);
            task->setTags(tags);
            task->setStartDate(dates.at(0));
            task->setEndDate(dates.at(1));
            return task;
        }

        FloatingTask* task = new FloatingTask();
        task->setName(description);
        task->setTags(tags);
        return task;
    }


    AddTaskCommand CommandParser::parseAdd(std::vector<std::string> inputArr) {
        if (inputArr.size() == 0) {
            throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
        }

        AbstractTask* task = parseTask(inputArr);
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
        } else if (inputArr.size() > 1) {
            throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
        }

        int taskID = std::stoi(inputArr.at(0));
        std::vector<std::string> subVec(inputArr.begin() + 1, inputArr.end());
        AbstractTask* task = parseTask(subVec);
        return EditTaskCommand(taskID, task);
    }


    DeleteTaskCommand CommandParser::parseDelete(std::vector<std::string> inputArr) {
        if (inputArr.size() == 0) {
            throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
        } else if (inputArr.size() > 1) {
            throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
        }

        int taskID = std::stoi(inputArr.at(0));
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
            throw std::invalid_argument(UNKNOWN_COMMAND_MESSAGE);
        }
    }
}


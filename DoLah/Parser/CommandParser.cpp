#include "CommandParser.h"

namespace DoLah {
    std::vector<std::string> CommandParser::ADD = { "add" };
    std::vector<std::string> CommandParser::SEARCH = { "search", "find" };
    std::vector<std::string> CommandParser::DONE = { "done" };
    std::vector<std::string> CommandParser::UNDONE = { "undone" };
    std::vector<std::string> CommandParser::EDIT = { "edit" };
    std::vector<std::string> CommandParser::DELETE = { "delete", "del", "dl" };
    std::vector<std::string> CommandParser::CLEAR = { "clear" };
    std::vector<std::string> CommandParser::UNDO = { "undo" };
    std::vector<std::string> CommandParser::REDO = { "redo" };

    std::string CommandParser::TOO_MANY_ARGUMENTS_MESSAGE = "Too many arguments";
    std::string CommandParser::TOO_LITTLE_ARGUMENTS_MESSAGE = "Too little arguments";
    std::string CommandParser::INVALID_TASK_ID_ARGUMENT = "Invalid task ID given";

    std::vector<std::string> CommandParser::OUTDATED = { "outdated", "overdue" };

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

    SetDoneTaskCommand CommandParser::parseSetDone(std::vector<std::string> inputArr) {
        if (inputArr.size() == 0) {
            throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
        } else if (inputArr.size() > 1) {
            throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
        }

        int taskID;
        try {
            taskID = std::stoi(inputArr.at(0));
            if (taskID < 0) {
                throw std::invalid_argument(INVALID_TASK_ID_ARGUMENT);
            }
        } catch (std::invalid_argument e) {
            throw std::invalid_argument(INVALID_TASK_ID_ARGUMENT);
        }
        return SetDoneTaskCommand(taskID-1);
    }

    SetUndoneTaskCommand CommandParser::parseSetUndone(std::vector<std::string> inputArr) {
        if (inputArr.size() == 0) {
            throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
        }
        else if (inputArr.size() > 1) {
            throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
        }

        int taskID;
        try {
            taskID = std::stoi(inputArr.at(0));
            if (taskID < 0) {
                throw std::invalid_argument(INVALID_TASK_ID_ARGUMENT);
            }
        }
        catch (std::invalid_argument e) {
            throw std::invalid_argument(INVALID_TASK_ID_ARGUMENT);
        }
        return SetUndoneTaskCommand(taskID-1);
    }

    SearchTaskCommand CommandParser::parseSearch(std::vector<std::string> inputArr) {
        if (inputArr.size() == 0) {
            throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
        }

        std::string arg = ParserLibrary::implode(inputArr, " ");

        return SearchTaskCommand(arg);
    }

    SearchDateTaskCommand CommandParser::parseSearchDate(std::vector<std::string> inputArr) {
        if (inputArr.size() == 0) {
            throw std::invalid_argument(TOO_LITTLE_ARGUMENTS_MESSAGE);
        }

        std::tm baseDate;
        std::tm searchDate;
        std::vector<std::tm> dates;

        if (inputArr.size() == 1 && ParserLibrary::inStringArray(OUTDATED, inputArr[0])) {
            baseDate = std::tm();
            searchDate = TimeManager::getCurrentTime();
        } else {
            dates = TaskTokenizer::findAndRemoveDate(inputArr);

            if (dates.size() == 1) {
                baseDate = TimeManager::getCurrentTime();
                searchDate = dates[0];
            } else if (dates.size() == 2) {
                baseDate = dates[0];
                searchDate = dates[1];
            } else {
                throw std::invalid_argument("");
            }
        }
        return SearchDateTaskCommand(baseDate, searchDate);
    }


    EditTaskCommand CommandParser::parseEdit(std::vector<std::string> inputArr) {
        if (inputArr.size() < 2) {
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
        return EditTaskCommand(taskID-1, task);
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
        return DeleteTaskCommand(taskID-1);
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

    std::vector<std::string> CommandParser::pruneCommand(std::vector<std::string> lineArr) {
        lineArr.erase(lineArr.begin());
        return lineArr;
    }


    RedoTaskCommand CommandParser::parseRedo(std::vector<std::string> inputArr) {
        if (inputArr.size() > 0) {
            throw std::invalid_argument(TOO_MANY_ARGUMENTS_MESSAGE);
        }

        RedoTaskCommand command;
        return command;
    }


    AbstractCommand* CommandParser::parse(std::string input) {
        input = ParserLibrary::removeDoubleSpacing(input);
        std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");
        std::string command = inputArr[0];

        if (ParserLibrary::inStringArray(ADD, command)) {
            inputArr = pruneCommand(inputArr);
            AddTaskCommand* command = new AddTaskCommand(parseAdd(inputArr));
            return command;
        } else if (ParserLibrary::inStringArray(SEARCH, command)) {
            inputArr = pruneCommand(inputArr);
            try {
                AbstractCommand* command = new SearchDateTaskCommand(parseSearchDate(inputArr));
                return command;
            } catch (std::invalid_argument e) {
                // continue
            }
            AbstractCommand* command = new SearchTaskCommand(parseSearch(inputArr));
            return command;
        } else if (ParserLibrary::inStringArray(DONE, command)) {
            inputArr = pruneCommand(inputArr);
            SetDoneTaskCommand* command = new SetDoneTaskCommand(parseSetDone(inputArr));
            return command;
        } else if (ParserLibrary::inStringArray(UNDONE, command)) {
            inputArr = pruneCommand(inputArr);
            SetUndoneTaskCommand* command = new SetUndoneTaskCommand(parseSetUndone(inputArr));
            return command;
        } else if (ParserLibrary::inStringArray(EDIT, command)) {
            inputArr = pruneCommand(inputArr);
            EditTaskCommand* command = new EditTaskCommand(parseEdit(inputArr));
            return command;
        } else if (ParserLibrary::inStringArray(DELETE, command)) {
            inputArr = pruneCommand(inputArr);
            DeleteTaskCommand* command = new DeleteTaskCommand(parseDelete(inputArr));
            return command;
        } else if (ParserLibrary::inStringArray(CLEAR, command)) {
            inputArr = pruneCommand(inputArr);
            ClearTaskCommand* command = new ClearTaskCommand(parseClear(inputArr));
            return command;
        } else if (ParserLibrary::inStringArray(UNDO, command)) {
            inputArr = pruneCommand(inputArr);
            UndoTaskCommand* command = new UndoTaskCommand(parseUndo(inputArr));
            return command;
        } else if (ParserLibrary::inStringArray(REDO, command)) {
            inputArr = pruneCommand(inputArr); 
            RedoTaskCommand* command = new RedoTaskCommand(parseRedo(inputArr));
            return command;
        } else {
            AddTaskCommand* command = new AddTaskCommand(parseAdd(inputArr));
            return command;
        }
    }
}


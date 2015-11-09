//@@author A0116631M
#pragma once
#include <stdio.h>
#include <iostream>
#include "Commands/Command.h"
#include "Models/CommandHistory.h"

namespace DoLah {
    /**
     * @class CommandInvoker CommandInvoker.h CommandInvoker.h
     * @brief This class is in charge of administrating AbstractCommands and their execution.
     *
     * It also adds relevant AbstractCommands to the CommandHistory.
     */
    class CommandInvoker {
    public:
        CommandInvoker();
        ~CommandInvoker();
        
        /**
         * @brief Setter for the CommandHistory pointer to add AbstractCommands to.
         *
         * @param history The pointer to the CommandHistory to use.
         */
        void setCmdHistory(CommandHistory*);

        /**
         * @brief Executes the command then checks if the command should be added to the 
         * CommandHistory.
         *
         * @param command The command to be executed.
         */
        void process(AbstractCommand*);

    private:
        CommandHistory* cmdHistory; ///< A pointer to the CommandHistory instance to add AbstractCommands to.

        /**
         * @brief This method checks whether the given AbstractCommand is a type that should not be 
         * included in the CommandHistory.
         * 
         * @param command The command to be checked.
         */
        bool checkIfExcludedCommandType(AbstractCommand * command);
    };

}
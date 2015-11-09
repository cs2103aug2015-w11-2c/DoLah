#pragma once

#include <stdio.h>
#include <vector>
#include <stack>
#include <fstream>
//#include "Models/Task.h"
#include "Models/Calendar.h"
#include "CommandInvoker.h"
#include "Config/ConfigurationManager.h"

namespace DoLah {
    /**
     * @class DoLahClient DoLahClient.h DoLahClient.h
     * @brief The client class which exposes API for any interface to utilise.
     *
     * In effect, it represents a session of the program.
     */
    class DoLahClient {
    public:
        DoLahClient();
        ~DoLahClient();

        /**
         * @brief Returns the Calendar object being used throughout this 
         * instance of the application.
         */
        Calendar getCalendar() const;

        /**
         * @brief Sets the location where the list of tasks will be stored.
         * 
         * @param location The path to save the output file.
         */
        void setStorageLocation(std::string);

        /**
         * @brief Sends a string to be parsed into an AbstractCommand, then
         * gets it executed.
         *
         * @param userInput The string to be processed.
         */
        void parseAndProcessCommand(std::string);

        void setTheme(int);

        /**
         * @brief Restarts the application.
         */
        void restart();
    private:
        Configuration config; ///< Configuration object for user settings.
        std::string settingsFile; ///< Path to the saved user settings. 
        DoLah::Calendar calendar; ///< The Calendar instance in use.
        DoLah::CommandInvoker commandInvoker; ///< The commandInvoker instance in use.
    };
}


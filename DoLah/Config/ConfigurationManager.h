//@@collate A0116631M
#pragma once

#include "Configuration.h"

namespace DoLah {
    /**
    * @class ConfigurationManager ConfigurationManager.h "Config/ConfigurationManager.h"
    * @brief Load or Save user Configuration.
    *
    * This class handles the loading and saving of the user Configuration object
    * Use the following class to retrieve the user Configuration.
    */
    class ConfigurationManager {
    public:
        ConfigurationManager();
        ~ConfigurationManager();

        /**
        * This static method will retrieve load the latest configuration from
        * the latest config.xml file.
        * @return the user Configuration
        */
        static Configuration loadConfig();

        /**
        * saveConfig static method will save the configuration into config.xml.
        * @param config     The Configuration object which will be saved
        */
        static void saveConfig(Configuration config);

    };

    static const std::string DEFAULT_CALENDAR_FILENAME = "calendar.yaml";
    static const int DEFAULT_THEME_NUMBER = 0;
}

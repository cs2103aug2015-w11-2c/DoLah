#pragma once

#include "Configuration.h"

namespace DoLah {
    class ConfigurationManager {
    public:
        ConfigurationManager();
        ~ConfigurationManager();

        static Configuration loadConfig();
        static void saveConfig(Configuration config);

    };

    static const std::string DEFAULT_CALENDAR_FILENAME = "calendar.yaml";
    static const int DEFAULT_THEME_NUMBER = 0;
}

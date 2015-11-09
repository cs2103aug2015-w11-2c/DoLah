//@@author A0116631M
#include "ConfigurationManager.h"
#include <fstream>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

namespace DoLah {
    ConfigurationManager::ConfigurationManager() {}

    ConfigurationManager::~ConfigurationManager() {}

    Configuration ConfigurationManager::loadConfig() {
        Configuration config;
        std::ifstream ifs("config.xml");
        try {
            boost::archive::xml_iarchive ia(ifs);
            ia >> BOOST_SERIALIZATION_NVP(config);
        } catch (const boost::archive::archive_exception&) {
            config.storagefile = DEFAULT_CALENDAR_FILENAME;
            config.theme = DEFAULT_THEME_NUMBER;
            ConfigurationManager::saveConfig(config);
        }
        return config;
    }

    void ConfigurationManager::saveConfig(Configuration config) {
        std::ofstream ofs("config.xml");
        boost::archive::xml_oarchive oa(ofs);
        oa << BOOST_SERIALIZATION_NVP(config);
    }
}

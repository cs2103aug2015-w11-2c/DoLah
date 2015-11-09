#pragma once
#include <string>
#include <fstream>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

namespace DoLah {
    /** 
     * @class Configuration
     * @brief The user configuration data structure.
     *
     * This class handles the serialization of configuration.
     * It takes care the saving and loading of the serialized configuration.
     * The format of the serialized format will be in XML.
     */
    class Configuration {
    private:
        friend class boost::serialization::access;

        /**
        * serialization of configuration into an XML format
        * For more information, check Boost save & load archive
        */
        template<class Archive>
        void save(Archive& ar, const unsigned int version) const {
            ar << BOOST_SERIALIZATION_NVP(storagefile);
            ar << BOOST_SERIALIZATION_NVP(theme);
        }

        /**
        * deserialize XML file into a configuration object.
        * For more information, check Boost save & load archive
        */
        template<class Archive>
        void load(Archive& ar, const unsigned int version) {
            ar >> BOOST_SERIALIZATION_NVP(storagefile);
            ar >> BOOST_SERIALIZATION_NVP(theme);
        }
        BOOST_SERIALIZATION_SPLIT_MEMBER()
    public:
        std::string storagefile; ///< The Calendar file path (either absolute path or relative path)
        int theme; ///< The themes number
    };
}

#pragma once
#include <string>
#include <fstream>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

namespace DoLah {
    class Configuration {
    private:
        friend class boost::serialization::access;

        template<class Archive>
        void save(Archive& ar, const unsigned int version) const {
            ar << BOOST_SERIALIZATION_NVP(storagefile);
        }

        template<class Archive>
        void load(Archive& ar, const unsigned int version) {
            ar >> BOOST_SERIALIZATION_NVP(storagefile);
        }
        BOOST_SERIALIZATION_SPLIT_MEMBER()
    public:
        std::string storagefile;
    };
}

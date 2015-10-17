#pragma once
#include "Models/Calendar.h"
#include <fstream>

#include <boost/date_time/posix_time/posix_time.hpp>

namespace DoLah {
    class CalendarStorage
    {
    public:
        CalendarStorage();
        ~CalendarStorage();

        static void save(const DoLah::Calendar &, const std::string &);
        static Calendar load(const std::string &);
    };
}


namespace YAML {
    template<>
    struct convert<std::tm> {
        static Node encode(const std::tm& rhs) {
            Node node;
            char s_dt[sizeof "2011-10-20 20:30:40"];
            std::strftime(s_dt, sizeof s_dt, "%F %T", &rhs);
            node = s_dt;
            return node;
        }

        static bool decode(const Node& node, std::tm& rhs) {
            if (!node.IsScalar()) {
                return false;
            }
            std::string s_datetime = node.as<std::string>();
            boost::posix_time::ptime t(boost::posix_time::time_from_string(s_datetime));
            rhs = boost::posix_time::to_tm(t);
            return true;
        }
    };
}
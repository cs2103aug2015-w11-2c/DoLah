//@@collate A0116631M
#pragma once
#include "Models/Calendar.h"
#include <fstream>

#include <boost/date_time/posix_time/posix_time.hpp>

namespace DoLah {
    /**
    * @brief This class handles the saving and loading of Calendar
    *
    * The Calendar will be stored in YAML format for readability.
    */
    class CalendarStorage
    {
    public:
        CalendarStorage();
        ~CalendarStorage();

        /**
        * @brief This method handles the saving of calendar
        *
        * @param [in] calendar The Calendar object that will be saved
        * @param [in] filename The filepath of yaml file.
        */
        static void save(const DoLah::Calendar &, const std::string &);

        /**
        * @brief This method handles the saving of Calendar
        *
        * @param [in] filename The filepath of yaml file.
        * @return The Calendar object that is loaded
        */
        static Calendar load(const std::string &);

    private:
        /**
         * @brief build yaml string from two task list: done and todo
         * @param todoNode The YAML::Node for todo task.
         * @param completedNode The YAML::Node for done task.
         * @return the string ready to be saved as a yaml file.
         */
        static std::string emitYAMLtoString(const YAML::Node&, const YAML::Node&);

        /**
         * @brief build the yaml string of the calendar.
         * @param calendar the Calendar object to build
         * @return yaml string ready to be stored.
         */
        static std::string buildCalendarYAML(const DoLah::Calendar&);

        /**
         * @brief build YAML::Node from the task
         * @param task the AbstractTask object that will be constructed.
         * @return YAML::Node of the task
         */
        static YAML::Node CalendarStorage::buildTaskNode(AbstractTask*);
    };
}


namespace YAML {
    /**
    * @brief This struct contains the date time serialization before storing and loading in YAML file.
    */
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
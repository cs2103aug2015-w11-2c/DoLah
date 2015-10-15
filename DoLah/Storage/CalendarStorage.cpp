#include "Storage/CalendarStorage.h"
#include "Models/Task.h"
#include <ctime>
#include <iostream>
#include <time.h>
#include <boost/date_time/posix_time/posix_time.hpp>
//#include <boost/filesystem.hpp>

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

namespace DoLah {
    CalendarStorage::CalendarStorage()
    {
    }


    CalendarStorage::~CalendarStorage()
    {
    }

    void CalendarStorage::save(const DoLah::Calendar& calendar, const std::string & filename) {
        std::vector<DoLah::AbstractTask*> taskList = calendar.getTaskList();
        YAML::Emitter out;



        YAML::Node todoNode;
        YAML::Node completedNode;

        for (auto it = taskList.begin(); it != taskList.end(); it++) {
            YAML::Node taskNode;
            taskNode["task"] = (*it)->getName();
            taskNode["description"] = (*it)->getDescription();
            if (!(*it)->getTags().empty()) {
                taskNode["tags"] = (*it)->getTags();
            }

            DoLah::FloatingTask* floatingTask = dynamic_cast<DoLah::FloatingTask*>(*it);
            DoLah::EventTask* eventTask = dynamic_cast<DoLah::EventTask*>(*it);
            DoLah::DeadlineTask* deadlineTask = dynamic_cast<DoLah::DeadlineTask*>(*it);

            if (eventTask != NULL) {
                taskNode["start"] = eventTask->getStartDate();
                taskNode["end"] = eventTask->getEndDate();
            }

            if (deadlineTask != NULL) {
                taskNode["due"] = deadlineTask->getDueDate();
            }

            if ((*it)->isDone()) {
                completedNode.push_back(taskNode);
            } else {
                todoNode.push_back(taskNode);
            }
        }

        out << YAML::BeginDoc;
        out << YAML::BeginMap;
        out << YAML::Key << "todo";

        out << YAML::Comment("Todo Tasks");
        out << YAML::Value << todoNode;
        out << YAML::Key << "done";
        out << YAML::Comment("Completed Tasks");
        out << YAML::Value << completedNode;
        out << YAML::EndMap;
        out << YAML::EndDoc;

        std::ofstream ofstream(filename);
        if (ofstream.is_open()) {
            ofstream << out.c_str();
        }
        ofstream.close();
    }

    Calendar CalendarStorage::load(const std::string& filename) {
        Calendar calendar;
        if (!std::ifstream(filename)) {
            std::ofstream out(filename);
            out.close();
        }
        YAML::Node node = YAML::LoadFile(filename);

        if (node.IsMap()) {
            for (auto it = node["todo"].begin(); it != node["todo"].end(); it++) {
                YAML::Node taskNode = *it;
                const std::string text;
                DoLah::AbstractTask* task = NULL;
                if (taskNode["due"].IsDefined()) {
                    DeadlineTask* d_task = new DeadlineTask;
                    d_task->setDueDate(taskNode["due"].as<std::tm>());
                    task = d_task;
                } else if (taskNode["start"].IsDefined() && taskNode["end"].IsDefined()) {
                    EventTask* e_task = new EventTask;
                    e_task->setStartDate(taskNode["start"].as<std::tm>());
                    e_task->setEndDate(taskNode["end"].as<std::tm>());
                    task = e_task;
                } else {
                    task = new FloatingTask;
                }
                task->setDone(false);
                task->setName(taskNode["task"].as<std::string>());
                task->setDescription(taskNode["description"].as<std::string>());
                calendar.addTask(task);
            }

            for (auto it = node["done"].begin(); it != node["done"].end(); it++) {
                YAML::Node taskNode = *it;
                const std::string text;
                DoLah::AbstractTask* task = NULL;
                if (taskNode["due"].IsDefined()) {
                    DeadlineTask* d_task = new DeadlineTask;
                    d_task->setDueDate(taskNode["due"].as<std::tm>());
                    task = d_task;
                } else if (taskNode["start"].IsDefined() && taskNode["end"].IsDefined()) {
                    EventTask* e_task = new EventTask;
                    e_task->setStartDate(taskNode["start"].as<std::tm>());
                    e_task->setEndDate(taskNode["end"].as<std::tm>());
                    task = e_task;
                } else {
                    task = new FloatingTask;
                }
                task->setDone(true);
                task->setName(taskNode["task"].as<std::string>());
                task->setDescription(taskNode["description"].as<std::string>());
                calendar.addTask(task);
            }
        }
        return calendar;
        
    }
}

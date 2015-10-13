#include "Storage/CalendarStorage.h"
#include "Models/Task.h"
#include <ctime>
#include <time.h>

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
            if (!node.IsSequence() || node.size() != 3) {
                return false;
            }
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

    void CalendarStorage::save(const DoLah::Calendar& calendar) {
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

        std::ofstream ofstream("calendar.yaml");
        if (ofstream.is_open()) {
            ofstream << out.c_str();
        }
        ofstream.close();
    }

    void CalendarStorage::load(DoLah::Calendar& calendar) {
        YAML::Node node = YAML::LoadFile("calendar.yaml");

        if (node.IsMap()) {
            for (auto it = node.begin(); it != node.end(); it++) {
                const std::string text;
                DoLah::AbstractTask* task = new FloatingTask;
                task->setName(it->as<std::string>());
                calendar.addTask(task);
            }
        }
        
    }
}
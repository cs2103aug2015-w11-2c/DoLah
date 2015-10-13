#include "Storage/CalendarStorage.h"
#include "../Models/Task.h"

namespace DoLah {
    CalendarStorage::CalendarStorage()
    {
    }


    CalendarStorage::~CalendarStorage()
    {
    }

    void CalendarStorage::save(const DoLah::Calendar& calendar) {
        std::vector<DoLah::AbstractTask*> taskList = calendar.getAllTask();
        YAML::Emitter out;
        for (auto it = taskList.begin(); it != taskList.end(); it++) {
            out << YAML::BeginSeq;
            out << (*it)->getName();
            out << YAML::EndSeq;
        }
        out << "HELLO";
    
        std::ofstream ofstream("storage.yaml");
        if (ofstream.is_open()) {
            ofstream << out.c_str();
        }
        ofstream.close();
    }

    void CalendarStorage::load(DoLah::Calendar& calendar) {
        YAML::Node node = YAML::LoadFile("storage.yaml");

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
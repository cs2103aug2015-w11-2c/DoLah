//@@collate A0116631M
#include "Storage/CalendarStorage.h"
#include "Models/Task.h"
#include <ctime>
#include <iostream>
#include <time.h>
//#include <boost/filesystem.hpp>


namespace DoLah {
    CalendarStorage::CalendarStorage() { }

    CalendarStorage::~CalendarStorage() { }

    YAML::Node CalendarStorage::buildTaskNode(AbstractTask* task) {
        YAML::Node taskNode;
        taskNode["task"] = task->getName();
        taskNode["description"] = task->getDescription();
        if (!task->getTags().empty()) {
            taskNode["tags"] = task->getTags();
        }

        DoLah::FloatingTask* floatingTask = dynamic_cast<DoLah::FloatingTask*>(task);
        DoLah::EventTask* eventTask = dynamic_cast<DoLah::EventTask*>(task);
        DoLah::DeadlineTask* deadlineTask = dynamic_cast<DoLah::DeadlineTask*>(task);

        if (eventTask != NULL) {
            taskNode["start"] = eventTask->getStartDate();
            taskNode["end"] = eventTask->getEndDate();
        }

        if (deadlineTask != NULL) {
            taskNode["due"] = deadlineTask->getDueDate();
        }
        return taskNode;
    }

    std::string CalendarStorage::buildCalendarYAML(const DoLah::Calendar& calendar) {

        std::vector<DoLah::AbstractTask*> taskList = calendar.getAllTaskList();
        YAML::Node todoNode;
        YAML::Node completedNode;

        for (auto it = taskList.begin(); it != taskList.end(); it++) {
            YAML::Node taskNode = buildTaskNode(*it);

            if ((*it)->isDone()) {
                completedNode.push_back(taskNode);
            } else {
                todoNode.push_back(taskNode);
            }
        }

        return emitYAMLtoString(todoNode, completedNode);
    }

    std::string CalendarStorage::emitYAMLtoString(const YAML::Node& todoNode, const YAML::Node& completedNode) {
        YAML::Emitter out;
        out << YAML::BeginDoc;
        if (todoNode.size() + completedNode.size() > 0) {
            out << YAML::BeginMap;
            if (todoNode.size() > 0) {
                out << YAML::Key << "todo"
                    << YAML::Comment("Todo Tasks")
                    << YAML::Value << todoNode;
            }
            if (completedNode.size() > 0) {
                out << YAML::Key << "done"
                    << YAML::Comment("Completed Tasks")
                    << YAML::Value << completedNode;
            }

            out << YAML::EndMap;
        }
        out << YAML::EndDoc;
        return out.c_str();
    }

    void CalendarStorage::save(const DoLah::Calendar& calendar, const std::string & filename) {
        std::string out = CalendarStorage::buildCalendarYAML(calendar);
        std::ofstream ofstream(filename);
        if (ofstream.is_open()) {
            ofstream << out;
        }
        ofstream.close();
    }

    Calendar CalendarStorage::load(const std::string& filename) {
        Calendar calendar;
        if (!std::ifstream(filename)) {
            std::ofstream out(filename);
            out.close();
        }
        YAML::Node node;
        try {
            node = YAML::LoadFile(filename);
        } catch (const YAML::ParserException&) {
            return calendar;
        } catch (const YAML::BadFile&) {
            return calendar;
        }

        if (node.IsMap()) {
            for (auto taskGroupIterator = node.begin(); taskGroupIterator != node.end(); ++taskGroupIterator) {
                std::string taskStatus = taskGroupIterator->first.as<std::string>();

                for (auto taskIterator = taskGroupIterator->second.begin(); taskIterator != taskGroupIterator->second.end(); ++taskIterator) {                    
                    YAML::Node taskNode = *taskIterator;
                    DoLah::AbstractTask* task = NULL;
                    const std::string text;
                    try {
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

                        if (!taskNode["tags"].IsNull()) {
                            for (auto tagIter = taskNode["tags"].begin(); tagIter != taskNode["tags"].end(); ++tagIter) {
                                task->addTag((*tagIter).as<std::string>());
                            }
                        }

                        if (taskStatus == "todo") {
                            task->setDone(false);
                        } else if (taskStatus == "done") {
                            task->setDone(true);
                        }
                        task->setName(taskNode["task"].as<std::string>());
                        task->setDescription(taskNode["description"].as<std::string>());

                    } catch (const std::exception&) {
                        // Load next item and ignore the rest of the operation.
                        delete task;
                        continue;
                    }
                    calendar.addTask(task);
                }
            }
        }
        calendar.updateTaskExpiry();
        return calendar;
        
    }
}

#pragma once
#include <string>
#include <chrono>
#include <yaml-cpp/yaml.h>
#include "ISerializable.h"
#include <vector>

namespace DoLah {
    class AbstractTask : public ISerializable {
    public:
        AbstractTask();
        virtual ~AbstractTask() = 0;
        void setId(int id);
        int getId();
        void setName(std::string);
        std::string getName();
        void setDescription(std::string);
        std::string getDescription();
        void setTags(std::vector<std::string>);
        std::vector<std::string> getTags();
        void setDone(bool);
        bool isDone();
    private:
        std::string description;
        std::string name;
        std::vector<std::string> tags;
        int id;
        bool done;
    };

    class FloatingTask : public AbstractTask {
        ISerializable* serialize(const std::string&);
        std::string deserialize();
    };

    class EventTask : public AbstractTask {
    public:
        EventTask();
        ~EventTask();
        ISerializable* serialize(const std::string&);
        std::string deserialize();
        std::tm getStartDate();
        void setStartDate(std::tm);
        std::tm getEndDate();
        void setEndDate(std::tm);
    private:
        std::tm startDate;
        std::tm endDate;
    };

    class DeadlineTask : public AbstractTask {
    public:
        DeadlineTask();
        ~DeadlineTask();
        ISerializable* serialize(const std::string&);
        std::string deserialize();
        std::tm getDueDate();
        void setDueDate(std::tm);
    private:
        std::tm dueDate;
    };
}

using DoLah::FloatingTask;
using DoLah::DeadlineTask;
using DoLah::EventTask;

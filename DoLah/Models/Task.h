#pragma once
#include <string>
#include <chrono>
#include <yaml-cpp/yaml.h>
#include "ISerializable.h"

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
        void setDone(bool);
        bool isDone();
    private:
        std::string description;
        std::string name;
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
        std::chrono::system_clock::time_point getStartDate();
        void setStartDate(std::chrono::system_clock::time_point);
        std::chrono::system_clock::time_point getEndDate();
        void setEndDate(std::chrono::system_clock::time_point);
        ISerializable* serialize(const std::string&);
        std::string deserialize();
    private:
        std::chrono::system_clock::time_point startDate;
        std::chrono::system_clock::time_point endDate;
    };

    class DeadlineTask : public AbstractTask {
    public:
        DeadlineTask();
        ~DeadlineTask();
        std::chrono::system_clock::time_point getDueDate();
        void setDueDate(std::chrono::system_clock::time_point);
        ISerializable* serialize(const std::string&);
        std::string deserialize();
    private:
        std::chrono::system_clock::time_point dueDate;
    };
}

using DoLah::FloatingTask;
using DoLah::DeadlineTask;
using DoLah::EventTask;
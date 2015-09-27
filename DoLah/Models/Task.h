#pragma once
#include <string>
#include <chrono>

namespace DoLah {
    class AbstractTask {
    public:
        class Serializer {
            static AbstractTask * serialize(std::string data);
            std::string deserialize();
        };
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

    class FloatingTask : public AbstractTask { };

    class EventTask : public AbstractTask {
    public:
        EventTask();
        ~EventTask();
        std::chrono::system_clock::time_point getStartDate();
        void setStartDate(std::chrono::system_clock::time_point);
        std::chrono::system_clock::time_point getEndDate();
        void setEndDate(std::chrono::system_clock::time_point);
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

    private:
        std::chrono::system_clock::time_point dueDate;
    };
}

using DoLah::FloatingTask;
using DoLah::DeadlineTask;
using DoLah::EventTask;
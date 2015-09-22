#pragma once
#include <string>
#include <chrono>


namespace DoLah {
    class Task {
    public:
        Task();
        virtual ~Task();
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

    class EventTask : Task {
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
}

using DoLah::Task;
using DoLah::EventTask;
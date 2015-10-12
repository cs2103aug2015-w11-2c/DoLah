#pragma once
#include <string>
#include <chrono>
#include <vector>

namespace DoLah {
    class AbstractTask {
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

    class FloatingTask : public AbstractTask {};

    class EventTask : public AbstractTask {
    public:
        EventTask();
        ~EventTask();
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
        std::tm getDueDate();
        void setDueDate(std::tm);

    private:
        std::tm dueDate;
    };
}

using DoLah::FloatingTask;
using DoLah::DeadlineTask;
using DoLah::EventTask;
#pragma once
#include <string>
#include <chrono>
#include <yaml-cpp/yaml.h>
#include <vector>

namespace DoLah {

    /// Abstract Task class is the base class for any Task.
    class AbstractTask {
    public:
        AbstractTask(); ///< default constructor
        virtual ~AbstractTask() = 0; ///< destructor
        void setId(int id); ///< set the Task ID
        int getId(); ///< get the Task ID
        void setName(std::string); ///< set the Task name
        std::string getName(); ///< get the Task name
        void setDescription(std::string); ///< set the Task description
        std::string getDescription(); ///< get the Task description
        void setDone(bool); ///< set the Task done flag
        bool isDone(); ///< get the Task done flag
		void setTags(std::vector<std::string>); ///< set the vector of tags assigned to the task.
		std::vector<std::string> getTags(); ///< get the vector of tags assigned to the task.

    private:
        std::string description; ///< A Detailed explanation about the task.
        std::string name; ///< Task name is the header of the task.
        int id; ///< Task identifier is used for the storage tracking.
        bool done; ///< a flag that mark whether a task has finished, and may be hide or cleared later.
		std::vector<std::string> tags; ///< Vector holding tags assigned to the task.
    };

    /// A floating task is a task without any time specified.
    class FloatingTask : public AbstractTask { };

    /// EventTask is a Task that have a specific starting datetime and ending datetime.
    class EventTask : public AbstractTask {
    public:
        EventTask(); ///< default constructor
        ~EventTask(); ///< destructor
        std::tm getStartDate(); ///< get the starting datetime
        void setStartDate(std::tm); ///< set the starting datetime
        std::tm getEndDate(); ///< get the ending datetime
        void setEndDate(std::tm); ///< set the ending datetime
    private:
        std::tm startDate; ///< Task starting datetime
        std::tm endDate; ///< Task ending datetime
    };

    /// DeadlineTask is a task that have a specific due datetime.
    class DeadlineTask : public AbstractTask {
    public:
        DeadlineTask(); ///< default constructor
        ~DeadlineTask(); ///< destructor
        std::tm getDueDate(); ///< get the due date
        void setDueDate(std::tm); ///< set the due date
    private:
        std::tm dueDate; ///< Task due datetime
    };
}

using DoLah::FloatingTask;
using DoLah::DeadlineTask;
using DoLah::EventTask;

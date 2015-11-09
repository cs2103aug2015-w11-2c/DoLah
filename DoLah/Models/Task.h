#pragma once
#include <string>
#include <chrono>
#include <yaml-cpp/yaml.h>
#include <vector>

#include <TimeManager.h>

namespace DoLah {

    /// Abstract Task class is the base class for any Task.
    class AbstractTask {
    public:
        AbstractTask(); ///< default constructor.
        virtual ~AbstractTask() = 0; ///< destructor.
        void setId(int id); ///< set the Task ID.
        int getId(); ///< get the Task ID.
        void setIndex(int); ///< set the Index of the Task.
        int getIndex(); ///< get the Index of the Task.
        void setName(std::string); ///< set the Task name.
        std::string getName(); ///< get the Task name.
        void setDescription(std::string); ///< set the Task description.
        std::string getDescription(); ///< get the Task description.
        void setDone(bool); ///< set the Task done flag.
        bool isDone(); ///< get the Task done flag.
        void setTags(std::vector<std::string>); ///< set the vector of tags assigned to the task.
        void addTag(std::string); ///< add a tag assigned to the task.
        std::vector<std::string> getTags(); ///< get the vector of tags assigned to the task.
        bool isExpired(); ///< get the flag for the Task's expiry        
        void setExpired(bool); ///< set the flag for the Task's expiry.
        virtual void updateExpired(); ///< virtual method to update an individual Task's expiry. 

        /**
         * @brief Compares two tasks. Returns the result of the assertion that the second task
         * is strictly greater than the first.
         *
         * @param first The first task to be compared.
         * @param second The second task to be compared.
         * @return true if and only if first < second. false otherwise.
         */
        static bool taskCompare(AbstractTask*, AbstractTask*);

        /**
         * @brief Retrieves any datetime items from a task. If it is an EventTask, the endDate
         * comes first.
         *
         * @param it The task to retreive datetime objects from.
         * @return A vector containing the dates.
         */
        static std::vector<std::tm> getDates(AbstractTask*);
    private:
        std::string description; ///< A detailed explanation about the task.
        std::string name; ///< Task name is the header of the task.
        int id; ///< Task identifier is used for the storage tracking.
        int index; ///< Index at which the task will be displayed in the GUI. @See Calendar::indexTasks();
        bool done; ///< a flag that mark whether a task has finished, and may be hide or cleared later.
		std::vector<std::string> tags; ///< Vector holding tags assigned to the task.
        bool expired = false; ////< flag for whether the task has expired.
    };

    /// A floating task is a task without any time specified.
    class FloatingTask : public AbstractTask { };

    /// EventTask is a Task that have a specific starting datetime and ending datetime.
    class EventTask : public AbstractTask {
    public:
        EventTask(); ///< default constructor.
        ~EventTask(); ///< destructor.
        std::tm getStartDate(); ///< get the starting datetime.
        void setStartDate(std::tm); ///< set the starting datetime.
        std::tm getEndDate(); ///< get the ending datetime.
        void setEndDate(std::tm); ///< set the ending datetime.
        virtual void updateExpired(); ///< Vector holding tags assigned to the task.
    private:
        std::tm startDate; ///< Task starting datetime.
        std::tm endDate; ///< Task ending datetime.
    };

    /// DeadlineTask is a task that have a specific due datetime.
    class DeadlineTask : public AbstractTask {
    public:
        DeadlineTask(); ///< default constructor.
        ~DeadlineTask(); ///< destructor.
        std::tm getDueDate(); ///< get the due date.
        void setDueDate(std::tm); ///< set the due date.
        virtual void updateExpired(); ///< Vector holding tags assigned to the task.
    private:
        std::tm dueDate; ///< Task due datetime.
    };
}

using DoLah::FloatingTask;
using DoLah::DeadlineTask;
using DoLah::EventTask;

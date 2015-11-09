#pragma once

#include <vector>
#include <algorithm>
#include "Models/Task.h"
#include <Models/CommandHistory.h>
#include "TimeManager.h"

namespace DoLah {
    /**
     * @class Calendar Calendar.h Models/Calendar.h
     * @brief Class for holding the actual tasklist(s) and any operations on tasks in those list(s).
     *  
     * This class holds all the tasks and contains all the possible operations onthe tasklists. 
     * Any operation on the tasklists must necessarily go through one of the methods in this class.
     * For all practical purposes only one copy of this class should exist in the program at any 
     * point of time.
     * All vectors in the class should be assumed to be sorted at all times.
     * Any new operation on the vectors to be defined should not violate this property.
     * It is not a singleton class only because of testing purposes and also 
     * encapsulation problems arising from creating a singleton class.
     */
    class Calendar {
    public:
        Calendar();
        ~Calendar();

        /**
         * @brief Returns the task at the given index in the main task list #taskList.
         *
         * @param index The target index.
         * @return A pointer to the relevant AbstractTask.
         */
        AbstractTask* getTask(int) const;

        /**
         * @brief Returns the task at the given index in the done task list #doneList.
         *
         * @param index The target index.
         * @return A pointer to the relevant AbstractTask.
         */
        AbstractTask* getDone(int) const;

        /**
         * @brief Returns a copy of #taskList as an actual vector object.
         *
         * @return A vector containing all undone tasks.
         */
        std::vector<AbstractTask*> getTaskList() const;
        
        /**
         * @brief Returns a copy of #doneList as an actual vector object.
         *
         * @return A vector containing all done tasks.
         */
        std::vector<AbstractTask*> getDoneList() const;
        
        /**
         * @brief Returns a copy of the vector containing the search results of the last query as
         * an actual object.
         *
         * @return A vector containing the search results of the last query.
         */
        std::vector<AbstractTask*> getSearchedTaskList() const;
        
        /**
         * @brief Returns a vector containing all tasks from #taskList and #doneList as an actual
         * object.
         *
         * @return A vector containing all tasks.
         */
        std::vector<AbstractTask*> getAllTaskList() const;
        
        /**
         * @brief Returns a pointer to the CommandHistory class instance associated with this 
         * particular Calendar instance.
         *
         * @return A pointer to an instance of CommandHistory.
         */
        CommandHistory* getCmdHistory();

        /** 
         * @brief Adds a task to either #doneList or #taskList depending on whether the task is done. 
         * The task is inserted into the vector at the appropriate index to maintain a sorted file.
         *
         * This function practises binary insertion.
         * @param task A pointer to the task to be inserted
         */
        void addTask(AbstractTask*);

        /**
         * @brief Deletes a task at the given index depending on which list it is in.
         * If no boolean is specified, the task is assumed to be in taskList.
         *
         * @param index The index in the relevant list to be deleted.
         * @param status Indicates which list to check. true for taskList and false for doneList.
         */
        void deleteTask(int, bool=true);

        /**
         * @brief Toggles the done state of a task at the given index depending on which list 
         * it is in. If no boolean is specified, the task is assumed to be undone.
         *
         * @param index The index in the relevant list to be toggled.
         * @param status Indicates the current state of the last and thus which list to check. 
         * true for taskList and false for doneList.
         */
        void setDoneTask(int, bool=true);

        /**
         * @brief Updates a task at the given index depending on whether it is done or undone
         * and consequently which list it is in. 
         *
         * This function is not a true update of the task. It simply deletes the old task and
         * adds the new task into the relevant vector.
         * @param index The index in the relevant list to be edited (actually deleted).
         * @param task The task to be added in the place of the old task.
         */
        void updateTask(int, AbstractTask*);

        /**
         * @brief Clears both #taskList and #doneList of all tasks.
         */
        void clearTasks();

        /**
         * @brief Searches both #taskList and #doneList for tasks that contain the query string in
         * their name. If query is an empty string then no tasks will be displayed.
         *
         * @param query The string to qualify a task to be included in the results.
         */
        void search(std::string);

        /**
         * @brief Searches both #taskList and #doneList for tasks with dates that fall between the
         * given date parameters.
         *
         * @param from A datetime object denoting the start time of the query.
         * @param to A datetime object denoting the end time of the query.
         * @see std::tm for more details on datetime objects.
         * @see Parser for more details on how datetime is parsed.
         */
        void searchDate(std::tm, std::tm);

        /**
         * @brief Sorts all the tasks in the given vector.
         *
         * @param unsortedTaskList A vector of tasks assumed to be unsorted.
         * @see taskCompare to see how tasks are compared. 
         */
        void sortTasks(std::vector<AbstractTask*>&);

        /**
         * @brief Compares two tasks. Returns the result of the assertion that the second task 
         * is strictly greater than the first.
         *
         * @param first The first task to be compared
         * @param second The second task to be compared
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

        /**
         * @brief Go through all the tasks and marks expired tasks as overdue.
         */
        void updateTaskExpiry();

        /**
         * @brief Updates the index fields of all tasks in the given vector starting from the given
         * index. This index is always equal to
         * its actual index in the vector plus one.
         * 
         * @param list The vector to be indexed.
         * @param startIndex The index to start from.
         */
        void indexTasks(std::vector<AbstractTask*>&, int=0);
    private:
        std::vector<AbstractTask*> taskList; ///< Vector of undone tasks. Always assumed to be sorted.
        std::vector<AbstractTask*> doneList; ///< Vector of done tasks. Always assumed to be sorted.
        CommandHistory cmdHistory; ///< The instance of CommandHistory associated with this Calendar.
        std::vector<AbstractTask*> searchedList; ///< Vector containing search results.

        std::string TASK_INDEX_OUT_OF_RANGE_MESSAGE = "Task index out of range";

        /**
         * @brief Binary insertion helper function for addTask().
         * The result is attached to the index field of the task to be inserted.
         *
         * This is a recursive function.
         * @params task The task to be inserted.
         * @params start The starting index of the search.
         * @params end The ending index of the search.
         */
        void Calendar::findInsertionPoint(AbstractTask* task, int start, int end);
    };
}

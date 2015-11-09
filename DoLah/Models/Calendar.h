//@@collate A0111275R
#pragma once

#include <vector>
#include <algorithm>
#include "Models/Task.h"
#include <Models/CommandHistory.h>
#include "TimeManager.h"

namespace DoLah {
    /**
     * @class Calendar Models/Calendar.h
     * @brief Class for holding the actual tasklist(s) and any operations on tasks in those list(s).
     *  
     * This class holds all the tasks and contains all the possible operations onthe tasklists. 
     * Any operation on the tasklists must necessarily go through one of the methods in this class.
     * For all practical purposes only one copy of this class should exist in the program at any 
     * point of time.
     * It is not a singleton class only because of testing purposes and also 
     * encapsulation problems arising from creating a singleton class.
     */
	class Calendar {
	public:
		Calendar();
		~Calendar();

        /**
         * @brief Returns the task at the given index in the main task list taskList.
         *
         * @param index The target index.
         * @return A pointer to the relevant AbstractTask.
        */
		AbstractTask* getTask(int) const;

        /**
         * @brief Returns the task at the given index in the done task list doneList.
         *
         * @param index The target index.
         * @return A pointer to the relevant AbstractTask.
        */
        AbstractTask* getDone(int) const;

        /**
         * @brief Returns a copy of taskList as an actual vector object.
         *
         * @return A vector containing all undone tasks.
        */
        std::vector<AbstractTask*> getTaskList() const;
        
        /**
         * @brief Returns a copy of doneList as an actual vector object.
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
         * @brief Returns a vector containing all tasks from taskList and doneList as an actual
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
		/// Adds a task to either doneList or taskList depending on whether the task is done. 
        /// The task is inserted into the vector at the appropriate index to maintain a sorted file.
        void addTask(AbstractTask*);
        void deleteTask(int, bool=true); ///< Deletes 
        void setDoneTask(int, bool=true);
		void updateTask(int, AbstractTask*);
		void clearTasks();
        void search(std::string);
        void searchDate(std::tm, std::tm);
        void sortTasks(std::vector<AbstractTask*>&);
        static bool taskCompare(AbstractTask*, AbstractTask*);
        static std::vector<std::tm> getDates(AbstractTask*);
        void updateTaskExpiry();
        void indexTasks(std::vector<AbstractTask*>&, int=0);
    private:
        std::vector<AbstractTask*> taskList;
        std::vector<AbstractTask*> doneList;
        CommandHistory cmdHistory;
        std::vector<AbstractTask*> searchedList;

        std::string TASK_INDEX_OUT_OF_RANGE_MESSAGE = "Task index out of range";

        void Calendar::findInsertionPoint(AbstractTask* task, int start, int end);
    };
}

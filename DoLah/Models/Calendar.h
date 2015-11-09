#pragma once

#include <vector>
#include <algorithm>
#include "Models/Task.h"
#include <Models/CommandHistory.h>
#include "TimeManager.h"

//@@collate Wilson

namespace DoLah {
    /** \class Calendar
     *  \brief Class for holding the actual tasklist(s) and any operations on tasks in those list(s).
     *  
     *  This class holds all the tasks and contains all the possible operations on the tasklists. Any operation on the tasklists
     *  must necessarily go through one of the methods in this class.
     *  For all practical purposes only one copy of this class should exist in the program at any point of time.
     *  It is not a singleton class only because of testing purposes and also encapsulation problems arising from creating a singleton class.
     */
	class Calendar {
	public:
		Calendar();
		~Calendar();

		AbstractTask* getTask(int) const; ///< Retrieve the task at the given index in the main task list taskList.
        AbstractTask* getDone(int) const; ///< Retrieve the task at the given index in the done task list doneList.
		std::vector<AbstractTask*> getTaskList() const;
        std::vector<AbstractTask*> Calendar::getDoneList() const;
        std::vector<AbstractTask*> getSearchedTaskList() const;
        std::vector<AbstractTask*> getAllTaskList() const;
        CommandHistory* Calendar::getCmdHistory();
		void addTask(AbstractTask*); 
        void addTask(AbstractTask*, int); 
        void deleteTask(int, bool=true);
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

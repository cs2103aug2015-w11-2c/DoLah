#pragma once

#include <vector>
#include <algorithm>
#include "Models/Task.h"
#include <Models/CommandHistory.h>
#include "TimeManager.h"

namespace DoLah {
	class Calendar {
	public:
		Calendar();
		~Calendar();

		AbstractTask* getTask(int) const;
        AbstractTask* getDone(int) const;
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

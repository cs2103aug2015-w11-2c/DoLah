#pragma once

#include <vector>
#include <algorithm>
#include "Models/Task.h"
#include "TimeManager.h"

namespace DoLah {
	class Calendar {
	public:
		Calendar();
		~Calendar();

		AbstractTask* getTask(int) const;
        AbstractTask* getDone(int) const;
		std::vector<AbstractTask*> getTaskList() const;
        std::vector<AbstractTask*> getDoneList() const;
        std::vector<AbstractTask*> getSearchedTaskList() const;
        std::vector<AbstractTask*> getAllTaskList() const;
		void addTask(AbstractTask*);
		void deleteTask(int);
        void setDoneTask(int, bool=true);
		void updateTask(int, AbstractTask*);
		void clearTasks();
        void search(std::string);
        void sortTasks(std::vector<AbstractTask*>&);
        static bool taskCompare(AbstractTask*, AbstractTask*);
        static std::vector<std::tm> getDates(AbstractTask*);
        void indexTasks(std::vector<AbstractTask*>&);
    private:
        std::vector<AbstractTask*> taskList;
        std::vector<AbstractTask*> doneList;
        std::vector<AbstractTask*> searchedList;

        std::string TASK_INDEX_OUT_OF_RANGE_MESSAGE = "Task index out of range";
    };
}

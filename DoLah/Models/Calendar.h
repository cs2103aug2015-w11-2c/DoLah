#pragma once

#include <vector>
#include "Models/Task.h"
#include <Models/CommandHistory.h>

namespace DoLah {
	class Calendar {
	public:
		Calendar();
		~Calendar();

		AbstractTask* getTask(int) const;
        AbstractTask* getDone(int) const;
		std::vector<AbstractTask*> getTaskList() const;
        std::vector<AbstractTask*> Calendar::getDoneList() const;
        std::vector<AbstractTask*> Calendar::getAllTaskList() const;
        CommandHistory* Calendar::getCmdHistory();
		void addTask(AbstractTask*);
		void deleteTask(int);
        void setDoneTask(int, bool=true);
		void updateTask(int, AbstractTask*);
		void clearTasks();
		std::vector<AbstractTask*> search(std::string);

    private:
        std::vector<AbstractTask*> taskList;
        std::vector<AbstractTask*> doneList;
        CommandHistory cmdHistory;

        std::string TASK_INDEX_OUT_OF_RANGE_MESSAGE = "Task index out of range";
    };
}

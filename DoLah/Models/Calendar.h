#pragma once

#include <vector>
#include "Models/Task.h"

namespace DoLah {
	class Calendar {
	public:
		Calendar();
		~Calendar();

		AbstractTask* getTask(int) const;
		std::vector<AbstractTask*> getTaskList() const;

		void addTask(AbstractTask*);
		void deleteTask(int);
		void updateTask(int, AbstractTask*);
		void clearTasks();
		std::vector<AbstractTask*> search(std::string);

	private:
		std::vector<AbstractTask*> taskList;

        std::string TASK_INDEX_OUT_OF_RANGE_MESSAGE = "Task index out of range";
	};
}

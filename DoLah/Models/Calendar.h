#pragma once

#include <vector>
#include "Models/Task.h"

namespace DoLah {
	class Calendar {
	public:
		Calendar();
		~Calendar();

		void addTask(AbstractTask*);
		void deleteTask(int);
		void updateTask(int, AbstractTask*);
		void clearTasks();
		AbstractTask* getTask(int);
		std::vector<AbstractTask*> search(std::string);
        	std::vector<AbstractTask*> getTaskList() const;

	private:
		std::vector<AbstractTask*> taskList;
	};
}

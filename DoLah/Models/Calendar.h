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
		void updateTask(AbstractTask*);
		void clearTasks();
		std::vector<AbstractTask*> search(std::string);
        std::vector<AbstractTask*> getTaskList();

	private:
		std::vector<AbstractTask*> taskList;
	};
}
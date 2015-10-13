#pragma once

#include <vector>
#include "Models/Task.h"


namespace DoLah {
	class Calendar {
	public:
		Calendar();
		~Calendar();

		std::vector<AbstractTask*> getTaskList();

		void addTask(AbstractTask*);
		void deleteTask(int);
		void updateTask(int, AbstractTask*);
		void clearTasks();
		std::vector<AbstractTask*> search(std::string);

	private:
		std::vector<AbstractTask*> taskList;
	};
}
#pragma once

#include <vector>
#include <algorithm>
#include "Models/Task.h"


namespace DoLah {
	class Calendar {
	public:
		Calendar();
		~Calendar();

		std::vector<AbstractTask*> getTaskList();

		void addTask(AbstractTask*);
		void deleteTask(int);
		void updateTask(AbstractTask*);
		void clearTasks();
		AbstractTask* getTask(int);
		std::vector<AbstractTask*> search(std::string);

		bool Calendar::TaskIdSearcher(int i);

	private:
		std::vector<AbstractTask*> taskList;
	};
}
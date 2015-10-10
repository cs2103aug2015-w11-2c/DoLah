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
		void updateTask(int, AbstractTask*);
		void clearTasks();
		std::vector<AbstractTask*> search(std::string);

		bool Calendar::TaskIdSearcher(int i);

	private:
		std::vector<AbstractTask*> taskList;
	};
}
#pragma once

#include <vector>
#include <iostream>

#include "Models/Task.h"

namespace DoLah {
	class Calendar {
	public:
        static Calendar& getInstance();

		~Calendar();

		void addTask(AbstractTask*);
		void deleteTask(int);
		void updateTask(int, AbstractTask*);
		void clearTasks();
		std::vector<AbstractTask*> search(std::string);
        std::vector<AbstractTask*> getTaskList();

        void printTaskList();
	private:
        Calendar::Calendar(Calendar const&) = delete;
        void operator=(Calendar const&) = delete;

        Calendar();

		std::vector<AbstractTask*> taskList;
	};
}
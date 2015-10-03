#include "Calendar.h"

namespace DoLah {
	Calendar::Calendar() {
	}
	
	Calendar::~Calendar() {
		//TODO
	}

	void Calendar::addTask(AbstractTask* task) {
		//TODO
	}

	void Calendar::deleteTask(int id) {
		//TODO
	}

	void Calendar::updateTask(AbstractTask*) {
		//TODO
	}

	AbstractTask* Calendar::getTask(int id) {
		//TODO

		return new FloatingTask;
	}
	
	std::vector<AbstractTask*> Calendar::search(std::string query) {
		std::vector<AbstractTask*> results;

		for (int i = 0; i < taskList.size(); i++) {
			if (taskList.at(i)->getName().find(query) != std::string::npos) {
				results.push_back(taskList.at(i));
			}
		}

		return results;
	}
}
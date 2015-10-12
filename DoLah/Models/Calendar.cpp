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

	void Calendar::deleteTask(int index) {
		taskList.erase(taskList.begin() + index);
	}

	void Calendar::updateTask(AbstractTask*) {
		//TODO
	}

    void Calendar::clearTasks() {
    }

	AbstractTask* Calendar::getTask(int id) {
		//TODO

		return new FloatingTask;
	}
	
    std::vector<AbstractTask*> Calendar::search(std::string query) {
        std::vector<AbstractTask*> results;

        return results;
    }
}
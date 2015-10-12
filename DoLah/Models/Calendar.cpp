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

    void Calendar::deleteTask(int) {
    }

    void Calendar::updateTask(int id, AbstractTask *) {
		
    }

    void Calendar::clearTasks() {
    }

	std::vector<AbstractTask*> Calendar::getTaskList() {
        return taskList;
    }

    std::vector<AbstractTask*> Calendar::search(std::string) {
        return std::vector<AbstractTask*>();
    }
}
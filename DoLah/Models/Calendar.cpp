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

    void Calendar::updateTask(AbstractTask *) {
    }

    void Calendar::clearTasks() {
    }

    AbstractTask * Calendar::getTask(int) {
        return nullptr;
    }

    std::vector<AbstractTask> Calendar::search(std::string) {
        return std::vector<AbstractTask>();
    }

	void deleteTask(int id) {
		//TODO
	}

	void updateTask(AbstractTask*) {
		//TODO
	}

	AbstractTask* getTask(int id) {
		//TODO

		return new FloatingTask;
	}
	
	std::vector<AbstractTask> search(std::string) {
		std::vector<AbstractTask> results;

		//TODO

		return results;
	}
}
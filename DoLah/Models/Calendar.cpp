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

    void Calendar::printTaskList() {
        for (size_t i = 0; i < taskList.size(); i++) {
            std::cout << i << ": " << this->taskList.at(i).getDescription();
        }
    }
}
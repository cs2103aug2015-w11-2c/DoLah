#include "Calendar.h"

namespace DoLah {

	Calendar::Calendar() {
	}
	
	Calendar::~Calendar() {
	}

	std::vector<AbstractTask*> Calendar::getTaskList() {
		return taskList;
	}

	void Calendar::addTask(AbstractTask* task) {
		if (taskList.empty()) {
			task->setId(1);
		}
		else {
			task->setId(taskList.back()->getId()+1);
		}
		taskList.push_back(task);
	}

	void Calendar::deleteTask(int index) {
		taskList.erase(taskList.begin() + index);
	}

	void Calendar::updateTask(AbstractTask* task) {

	}

	void Calendar::clearTasks() {
		taskList.clear();
	}
	
	std::vector<AbstractTask*> Calendar::search(std::string query) {
		std::vector<AbstractTask*> results;

		return results;
	}

    std::vector<AbstractTask*> Calendar::getAllTask() const
    {
        return this->taskList;
    }
}

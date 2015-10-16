#include "Calendar.h"

namespace DoLah {
	Calendar::Calendar() {
	}
	
	Calendar::~Calendar() {
		//TODO
	}

	void Calendar::addTask(AbstractTask* task) {
		if (taskList.empty()) {
			task->setId(1);
		}
		else {
			task->setId(taskList.back()->getId() + 1);
		}
		taskList.push_back(task);
	}

    void Calendar::deleteTask(int index) {
        taskList.erase(taskList.begin() + index);
    }

	void Calendar::updateTask(int taskIndex, AbstractTask* task) {
        size_t index = taskIndex;
        taskList.at(index) = task;
	}

	void Calendar::clearTasks() {
		taskList.clear();
	}
	
	std::vector<AbstractTask*> Calendar::search(std::string query) {
		std::vector<AbstractTask*> results;

		for (int i = 0; i < taskList.size(); i++) {
			if (taskList[i]->getName().find(query) != std::string::npos) {
				results.push_back(taskList.at(i));
			}
		}
		return results;
	}

    std::vector<AbstractTask*> Calendar::getTaskList() const
    {
        return this->taskList;
    }
}

#include "Calendar.h"

namespace DoLah {
	Calendar::Calendar() {
	}
	
	Calendar::~Calendar() {
		//TODO
	}

	AbstractTask* Calendar::getTask(int index) const {
		return taskList.at(index);
	}

	std::vector<AbstractTask*> Calendar::getTaskList() const {
		return taskList;
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
        if (index > taskList.size()) {
            throw std::out_of_range(TASK_INDEX_OUT_OF_RANGE_MESSAGE);
        }
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
}

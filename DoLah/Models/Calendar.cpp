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
		} else {
			task->setId(taskList.size());
		}
		taskList.push_back(task);
	}

	void Calendar::deleteTask(int index) {

	}

	void Calendar::updateTask(int index, AbstractTask* task) {
		AbstractTask* storedInfo = taskList[index];
		
		if (!task->getName().empty()) {
			storedInfo->setName(task->getName());
		}

		if (!task->getDescription().empty()) {
			storedInfo->setDescription(task->getDescription());
		}

		if (storedInfo->isDone() != task->isDone()) {
			storedInfo->setDone(!storedInfo->isDone());
		}
	}

	void Calendar::clearTasks() {
		taskList.clear();
	}

	std::vector<AbstractTask*> Calendar::search(std::string query) {
		std::vector<AbstractTask*> results;

		return results;
	}
}
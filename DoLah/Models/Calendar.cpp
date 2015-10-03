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

	void Calendar::deleteTask(int id) {
		
	}

	void Calendar::updateTask(AbstractTask*) {
		//TODO
	}

	void Calendar::clearTasks() {

	}

	AbstractTask* Calendar::getTask(int id) {
		return *(std::find(taskList.begin(), taskList.end(), id));
	}
	
	std::vector<AbstractTask*> Calendar::search(std::string query) {
		
	}
}
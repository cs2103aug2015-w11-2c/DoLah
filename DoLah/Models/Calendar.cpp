#include "Calendar.h"

namespace DoLah {
	Calendar::Calendar() {
        this->cmdHistory = DoLah::CommandHistory();
	}
	
	Calendar::~Calendar() {
		//TODO
	}

	AbstractTask* Calendar::getTask(int index) const {
		return taskList.at(index);
	}

    AbstractTask* Calendar::getDone(int index) const {
        return doneList.at(index);
    }

	std::vector<AbstractTask*> Calendar::getTaskList() const {
        return this->taskList;
	}

    std::vector<AbstractTask*> Calendar::getDoneList() const {
        return this->doneList;
    }

    std::vector<AbstractTask*> Calendar::getAllTaskList() const {
        std::vector<AbstractTask*> allTaskList;
        allTaskList.reserve(taskList.size() + doneList.size());
        allTaskList.insert(allTaskList.end(), taskList.begin(), taskList.end());
        allTaskList.insert(allTaskList.end(), doneList.begin(), doneList.end());
        return allTaskList;
    }

    DoLah::CommandHistory* Calendar::getCmdHistory(){
        DoLah::CommandHistory* cmdHistoryPointer = &(this->cmdHistory);
        return cmdHistoryPointer;
    }

	void Calendar::addTask(AbstractTask* task) {
		if (taskList.empty()) {
			task->setId(1);
		}
		else {
			task->setId(taskList.back()->getId() + 1);
		}

        if (task->isDone()) {
            doneList.push_back(task);
        } else {
		    taskList.push_back(task);
        }
	}

    void Calendar::addTask(AbstractTask* task, int index) {
        task->setId(index);

        if (task->isDone()) {
            doneList.insert(doneList.begin()+index, task);
        }
        else {
            taskList.insert(taskList.begin()+index, task);
        }
    }

    void Calendar::deleteTask(int index, bool status) {
        if (index >= taskList.size()) {
            throw std::out_of_range(TASK_INDEX_OUT_OF_RANGE_MESSAGE);
        }

        if (status) {
            taskList.erase(taskList.begin() + index);
        }
        else {
            taskList.erase(doneList.begin() + index);
        }
    }

    void Calendar::setDoneTask(int taskIndex, bool status) {
        AbstractTask* task;
        if (status) {
            // set task to done (from taskList to donelist)
            task = taskList.at(taskIndex);
            task->setDone(status);
            auto it_start = taskList.begin() + taskIndex;
            auto it_end = it_start + 1;
            std::move(it_start, it_end, std::back_inserter(doneList));
            taskList.erase(it_start, it_end);
        } else {
            // set task to undone (from donelist to tasklist)
            task = doneList.at(taskIndex);
            task->setDone(status);
            auto it_start = doneList.begin() + taskIndex;
            auto it_end = it_start + 1;
            std::move(it_start, it_end, std::back_inserter(taskList));
            doneList.erase(it_start, it_end);
        }

    }

	void Calendar::updateTask(int taskIndex, AbstractTask* task) {
        size_t index = taskIndex;
        taskList.at(index) = task;
	}

    void Calendar::clearTasks() {
        this->taskList.clear();
        this->doneList.clear();
    }
	
	std::vector<AbstractTask*> Calendar::search(std::string query) {
		std::vector<AbstractTask*> results;
	
		for (int i = 0; i < taskList.size(); i++) {
			if (taskList[i]->getName().find(query) != std::string::npos) {
				results.push_back(taskList.at(i));
			}
		}
        for (int i = 0; i < doneList.size(); i++) {
            if (doneList[i]->getName().find(query) != std::string::npos) {
                results.push_back(doneList.at(i));
            }
        }
		return results;
	}
}

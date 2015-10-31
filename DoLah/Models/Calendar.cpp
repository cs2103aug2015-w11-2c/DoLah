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

	void Calendar::addTask(AbstractTask* task) {
		if (taskList.empty()) {
			task->setId(1);
		}
		else {
			task->setId(taskList.back()->getId() + 1);
		}

        if (task->isDone()) {
            doneList.push_back(task);
            sortTasks(doneList);
        } else {
		    taskList.push_back(task);
            sortTasks(taskList);
        }
	}

    void Calendar::deleteTask(int index) {
        if (index >= taskList.size()) {
            throw std::out_of_range(TASK_INDEX_OUT_OF_RANGE_MESSAGE);
        }
        taskList.erase(taskList.begin() + index);
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

        sortTasks(taskList);
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

    void Calendar::sortTasks(std::vector<AbstractTask*> &unsortedTaskList) {
        std::sort(unsortedTaskList.begin(), unsortedTaskList.end(), taskCompare);
    }

    bool Calendar::taskCompare(AbstractTask* first, AbstractTask* second) {
        std::vector<std::tm> firstDates = getDates(first);
        std::vector<std::tm> secondDates = getDates(second);

        if (firstDates.size() != secondDates.size()) {
            return firstDates.size() > secondDates.size();
        } else if (firstDates.size() == 1) {
            int diff = TimeManager::compareTime(firstDates[0], secondDates[0]);
            if (diff != 0) {
                return diff > 0;
            }
            return first->getDescription().compare(second->getDescription()) > 0;
        } else if (firstDates.size() == 2) {
            int diff = TimeManager::compareTime(firstDates[0], secondDates[0]);
            if (diff != 0) {
                return diff > 0;
            }
            diff = TimeManager::compareTime(firstDates[1], secondDates[1]);
            if (diff != 0) {
                return diff > 0;
            }
            return first->getDescription().compare(second->getDescription()) > 0;
        }

        return false;
    }

    std::vector<std::tm> Calendar::getDates(AbstractTask *it) {
        std::vector<std::tm> dates;

        DoLah::FloatingTask* floatingTask = dynamic_cast<DoLah::FloatingTask*>(it);
        DoLah::EventTask* eventTask = dynamic_cast<DoLah::EventTask*>(it);
        DoLah::DeadlineTask* deadlineTask = dynamic_cast<DoLah::DeadlineTask*>(it);

        if (eventTask != NULL) {
            dates.push_back(eventTask->getEndDate());
            dates.push_back(eventTask->getStartDate());
        }

        if (deadlineTask != NULL) {
            dates.push_back(deadlineTask->getDueDate());
        }

        return dates;
    }


}

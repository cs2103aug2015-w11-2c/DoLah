#include "Calendar.h"

namespace DoLah {
    Calendar& Calendar::getInstance() {
        static Calendar instance;
        return instance;
    }

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

        printTaskList(this->taskList);
	}

    void Calendar::deleteTask(int index) {
        taskList.erase(taskList.begin() + index);

        printTaskList(this->taskList);
    }

	void Calendar::updateTask(int taskIndex, AbstractTask* task) {
        size_t index = taskIndex;
        taskList.at(index) = task;

        printTaskList(this->taskList);
	}

	void Calendar::clearTasks() {
		taskList.clear();

        printTaskList(this->taskList);
	}
	
	std::vector<AbstractTask*> Calendar::search(std::string query) {
		std::vector<AbstractTask*> results;

		for (int i = 0; i < taskList.size(); i++) {
			if (taskList[i]->getName().find(query) != std::string::npos) {
				results.push_back(taskList.at(i));
			}
		}

        printTaskList(results);
		return results;
	}
    std::vector<AbstractTask*> Calendar::getTaskList() {
        return this->taskList;
    }

    void Calendar::printTaskList(std::vector<AbstractTask*> taskList) {
        std::cout << "<<<<< TASK LIST >>>>> " << std::endl << "(size: " << taskList.size() << ")" << std::endl;
        for (size_t i = 0; i < taskList.size(); i++) {
            std::cout << (i) << ": ";
            std::string out = taskList.at(i)->toString();
            
            std::vector<std::tm> dates = taskList.at(i)->getDates();
            if (dates.size() == 1) {
                std::string dateString = "; " + std::to_string(dates.at(0).tm_mday) + "/"
                    + std::to_string(dates.at(0).tm_mon + 1) + "/"
                    + std::to_string(dates.at(0).tm_year + 1900);
                out += dateString;
            }

            std::cout << out << std::endl;
        }
        std::cout << std::endl;
    }
}
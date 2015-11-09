#include "Calendar.h"

namespace DoLah {
	Calendar::Calendar() {
        this->cmdHistory = DoLah::CommandHistory();
        this->lastQuery = "";
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

    std::vector<AbstractTask*> Calendar::getSearchedTaskList() const {
        return this->searchedList;
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
        if (task->isDone()) {
            findInsertionPoint(task, 0, doneList.size());
            doneList.insert(doneList.begin() + task->getIndex(), task);
            indexTasks(doneList, task->getIndex());
        } else {
            findInsertionPoint(task, 0, taskList.size());
            taskList.insert(taskList.begin() + task->getIndex(), task);
            indexTasks(taskList, task->getIndex());
        }

        this->updateSearch();
    }

    void Calendar::deleteTask(int index, bool status) {
        if (index >= taskList.size()) {
            throw std::out_of_range(TASK_INDEX_OUT_OF_RANGE_MESSAGE);
        }

        if (status) {
            taskList.erase(taskList.begin() + index);
            indexTasks(taskList);
        }
        else {
            taskList.erase(doneList.begin() + index);
            indexTasks(doneList);
        }

        this->updateSearch();
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
            indexTasks(taskList);
            sortTasks(doneList);
        } else {
            // set task to undone (from donelist to tasklist)
            task = doneList.at(taskIndex);
            task->setDone(status);
            auto it_start = doneList.begin() + taskIndex;
            auto it_end = it_start + 1;
            std::move(it_start, it_end, std::back_inserter(taskList));
            doneList.erase(it_start, it_end);
            indexTasks(doneList);
            sortTasks(taskList);
        }

        this->updateSearch();
    }

    void Calendar::updateTask(int taskIndex, AbstractTask* task) {
        size_t index = taskIndex;
        deleteTask(index);
        addTask(task);
        this->updateSearch();
    }

    void Calendar::clearTasks() {
        this->taskList.clear();
        this->doneList.clear();
        this->updateSearch();
    }

    void Calendar::search(std::string query) {
        this->lastQuery = query;
        std::vector<AbstractTask*> results;

        if (query == "") {
            results.clear();
        } else {
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
            this->searchedList = results;
        }  
    }

    void Calendar::searchDate(std::tm from, std::tm to) {
        std::vector<AbstractTask*> results;

        for (int i = 0; i < taskList.size(); i++) {
            std::vector<std::tm> dates = AbstractTask::getDates(taskList[i]);
            if (dates.size() == 0) {
                continue;
            }
            if (TimeManager::compareTime(from, dates[0]) >= 0 && TimeManager::compareTime(dates[0], to) >= 0) {
                results.push_back(taskList.at(i));
            }
        }
        for (int i = 0; i < doneList.size(); i++) {
            std::vector<std::tm> dates = AbstractTask::getDates(doneList[i]);
            if (dates.size() == 0) {
                continue;
            }
            if (TimeManager::compareTime(from, dates[0]) > 0 && TimeManager::compareTime(dates[0], to) > 0) {
                results.push_back(doneList.at(i));
            }
        }
        this->searchedList = results;
    }

    void Calendar::sortTasks(std::vector<AbstractTask*> &unsortedTaskList) {
        std::sort(unsortedTaskList.begin(), unsortedTaskList.end(), AbstractTask::taskCompare);
        indexTasks(unsortedTaskList);
    }

    void Calendar::indexTasks(std::vector<AbstractTask*> &list, int startIndex) {
        for (size_t index = startIndex; index < list.size(); index++) {
            list[index]->setIndex(index);
        }
    }

    void Calendar::updateTaskExpiry() {
        for (size_t i = 0; i < this->taskList.size(); i++) {
            this->taskList[i]->updateExpired();
        }
    }

    void Calendar::updateSearch() {
        this->search(lastQuery);
    }

    void Calendar::findInsertionPoint(AbstractTask* task, int start, int end) {
        if (end == start) {
            task->setIndex(start);
        }
        else {
            int middle = (start + end) / 2;
            if (task->isDone()) {
                if (AbstractTask::taskCompare(task, doneList[middle])) {
                    findInsertionPoint(task, start, middle);
                }
                else {

                    findInsertionPoint(task, middle + 1, end);
                }
            }
            else {
                if (AbstractTask::taskCompare(task, taskList[middle])) {
                    findInsertionPoint(task, start, middle);
                }
                else {
                    findInsertionPoint(task, middle + 1, end);
                }
            }
        }
    }
}

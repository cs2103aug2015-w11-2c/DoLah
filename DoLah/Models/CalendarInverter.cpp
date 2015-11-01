#include "CalendarInverter.h"

DoLah::CalendarInverter::CalendarInverter(){
}

DoLah::CalendarInverter::~CalendarInverter(){
}

void DoLah::CalendarInverter::invertAdd(AbstractTask * task, Calendar * calendar){
    int targetId;
    if (task->isDone()) {
        targetId = calendar->getDoneList().size() - 1;
    }
    else {
        targetId = calendar->getTaskList().size() - 1;
    }
    calendar->deleteTask(targetId);
}

void DoLah::CalendarInverter::invertDelete(AbstractTask * task, int taskIndex, Calendar * calendar){
    calendar->addTask(task, taskIndex);
}

void DoLah::CalendarInverter::invertEdit(AbstractTask * task, int taskIndex, Calendar * calendar){
    calendar->updateTask(taskIndex, task);
}

void DoLah::CalendarInverter::invertClear(std::vector<AbstractTask*> taskList, Calendar * calendar){
    for (int i = 0; i < taskList.size(); i++) {
        calendar->addTask(taskList.at(i));
    }
}

void DoLah::CalendarInverter::invertSearch(std::vector<AbstractTask*> ** resultVector, std::string query, Calendar * calendar){
    **resultVector = (calendar->search(query));
}

void DoLah::CalendarInverter::invertDone(AbstractTask * task, Calendar * calendar){
    std::vector<AbstractTask *> doneList = calendar->getDoneList();
    for (int i = 0; i < doneList.size(); i++) {
        if (task->getName() == doneList[i]->getName()){
            if (task->getDescription() == doneList[i]->getDescription()){
                if (task->getId() == doneList[i]->getId()){
                    calendar->setDoneTask(i, false);
                    break;
                }
            }
        }
    }
}

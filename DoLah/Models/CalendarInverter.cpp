#include "CalendarInverter.h"

DoLah::CalendarInverter::CalendarInverter(){
}

DoLah::CalendarInverter::~CalendarInverter(){
}

void DoLah::CalendarInverter::invertAdd(AbstractTask * task, Calendar * calendar){
    calendar->deleteTask(task->getId(), !(task->isDone()));
}

void DoLah::CalendarInverter::invertDelete(AbstractTask * task, Calendar * calendar){
    calendar->addTask(task, task->getId());
}

void DoLah::CalendarInverter::invertEdit(AbstractTask * task, Calendar * calendar){
    calendar->updateTask(task->getId(), task);
}

void DoLah::CalendarInverter::invertClear(std::vector<AbstractTask*> taskList, Calendar * calendar){
    for (int i = 0; i < taskList.size(); i++) {
        calendar->addTask(taskList.at(i));
    }
}

void DoLah::CalendarInverter::invertSearch(std::vector<AbstractTask*> ** resultVector, std::string query, Calendar * calendar){
    calendar->search(query);
}

void DoLah::CalendarInverter::invertDone(AbstractTask * task, Calendar * calendar){
    bool done;
    std::vector<AbstractTask *> taskList;

    if (task->isDone()) {
        done = false;
        taskList = calendar->getDoneList();
    }
    else {
        done = true;
        taskList = calendar->getTaskList();
    }

    for (int i = 0; i < taskList.size(); i++) {
        if (task->getName() == taskList[i]->getName()){
            if (task->getDescription() == taskList[i]->getDescription()){
                if (task->getId() == taskList[i]->getId()){
                    calendar->setDoneTask(i, done);
                    break;
                }
            }
        }
    }
}

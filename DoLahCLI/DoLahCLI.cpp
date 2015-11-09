//@@collate A0116631M
#include "DoLahCLI.h"
#include <time.h>
#include <stdlib.h>

void startConsole() {
    DoLah::DoLahClient client;
    std::cout << "Welcome to DoLah! " << std::endl;

    while (true) {
        try {
            printCalendar(client.getCalendar());
            std::cout << "Please enter a command: ";
            std::string command;
            getline(std::cin, command);
            client.parseAndProcessCommand(command);
            std::cout << "Your command \"" << command << "\" has been executed." << std::endl;
        }
        catch (std::exception e) {
            std::cout << "thr fuck" << std::endl;
            std::cout << e.what() << std::endl;
        }
    }
}

void printCalendar(const DoLah::Calendar& calendar){
    std::vector<DoLah::AbstractTask*> taskList = calendar.getTaskList();
    //std::system("cls");
    std::cout << "<<<<< TASK LIST >>>>> " << std::endl << "(size: " << taskList.size() << ")" << std::endl;

    for (size_t i = 0; i < taskList.size(); i++) {
        std::cout << i << ": " << taskList[i]->getName() << std::endl;

        if (!taskList[i]->getTags().empty()) {
            std::vector<std::string> tags = taskList[i]->getTags();
            std::cout << "   tags: ";
            for (size_t j = 0; j < tags.size(); j++) {
                std::cout << "#" << tags[j] << " ";
            }
            std::cout << std::endl;
        }

        DoLah::FloatingTask* floatingTask = dynamic_cast<DoLah::FloatingTask*>(taskList[i]);
        DoLah::EventTask* eventTask = dynamic_cast<DoLah::EventTask*>(taskList[i]);
        DoLah::DeadlineTask* deadlineTask = dynamic_cast<DoLah::DeadlineTask*>(taskList[i]);

        if (eventTask != NULL) {
            std::tm startDate = eventTask->getStartDate();
            std::tm endDate = eventTask->getEndDate();
            char s_startDatetime[sizeof "2011-10-20 20:30:40"];
            strftime(s_startDatetime, sizeof(s_startDatetime), "%F %T", &startDate);
            char s_endDatetime[sizeof "2011-10-20 20:30:40"];
            strftime(s_endDatetime, sizeof s_endDatetime, "%F %T", &endDate);
            std::cout << "   from: " << std::string(s_startDatetime) << std::endl;
            std::cout << "   to: " << std::string(s_endDatetime) << std::endl;
        }

        if (deadlineTask != NULL) {
            std::tm dueDate = deadlineTask->getDueDate();
            char s_dueDatetime[sizeof "2011-10-20 20:30:40"];
            strftime(s_dueDatetime, sizeof(s_dueDatetime), "%F %T", &dueDate);
            std::cout << "   on: " << std::string(s_dueDatetime) << std::endl;
        }
    }
    std::cout << std::endl;
}
#include "DoLahCLI.h"

void startConsole() {
    DoLah::DoLahClient client;
    std::cout << "Welcome to DoLah! " << std::endl;

    while (true) {
        printCalendar(client.getCalendar());
        std::cout << "Please enter a command: ";
        std::string command;
        getline(std::cin, command);
        client.parseAndProcessCommand(command);
        std::cout << "Your command \"" << command << "\" has been executed." << std::endl;
    }
}

void printCalendar(const DoLah::Calendar& calendar){
    std::vector<DoLah::AbstractTask*> taskList = calendar.getTaskList();
    for (size_t i = 0; i < taskList.size(); i++) {
        std::cout << i << ": " << taskList[i]->getName() << "\n";
    }
}

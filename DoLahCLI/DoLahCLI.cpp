#include "DoLahCLI.h"

void startConsole() {
    DoLah::DoLahClient client;
    while (true) {
        std::cout << "Welcome to DoLah! Please enter a command: ";
        std::string command;
        getline(std::cin, command);
        client.parseAndProcessCommand(command);
        std::cout << "Your command \"" << command << "\" has been executed." << std::endl;

    }
}

void printTaskList(const Calendar& calendar){
    std::vector<DoLah::AbstractTask*> taskList = calendar.getTaskList();
    for (size_t i = 0; i < taskList.size(); i++) {
        std::cout << i << ": " << taskList[i]->getDescription() << "\n";
    }
}

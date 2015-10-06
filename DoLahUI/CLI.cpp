#include <DoLahUI.h>

void startConsole() {
    while (true) {
        std::cout << "Welcome to DoLah! Please enter a command: ";
        std::string command;
        getline(std::cin, command);
        appClient.parseAndProcessCommand(command);
        std::cout << "Your command \"" << command << "\" has been executed." << std::endl;
    }
}
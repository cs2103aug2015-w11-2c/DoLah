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
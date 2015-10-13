#include "DoLahCLI.h"

void startConsole() {
    DoLah::DoLahClient client;
    std::cout << "Welcome to DoLah!" << std::endl;
    while (true) {
        std::string command;
        std::cout << "Please enter a command: ";
        getline(std::cin, command);
        try {
            client.parseAndProcessCommand(command);
            std::cout << "Your command \"" << command << "\" has been executed." << std::endl;
            std::cout << std::endl;
        } catch (std::invalid_argument e) {
            std::cout << "Invalid command: " << e.what() << "\n";
        }
    }
}
#include "DoLahCLI.h"

void startConsole() {
    DoLah::DoLahClient client;
    std::cout << "Welcome to DoLah!" << std::endl;
    while (true) {
        std::string command;
        std::cout << "Please enter a command: ";
        getline(std::cin, command);
        
        if (command == "") {
            continue;
        }

        if (DoLah::ParserLibrary::tolowercase(DoLah::ParserLibrary::strip(command)) == "exit") {
            std::cout << "Press Enter to exit." << std::endl;
            getline(std::cin, command);
            return;
        }
        try {
            client.parseAndProcessCommand(command);
        } catch (std::invalid_argument e) {
            std::cout << "Invalid command: " << e.what() << "\n";
        }
    }
}
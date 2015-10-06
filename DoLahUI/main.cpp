#include "DoLahUI.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        QApplication app(argc, argv);
        DoLahUI window;
        window.show();
        FreeConsole();
        return app.exec();
    }
    else {
        while (true) {
            std::cout << "command: ";
            std::string command;
            getline(std::cin, command);
            std::cout << command << " has been executed." << std::endl;
        }
        return 0;
    }
}

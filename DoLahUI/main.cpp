#include "DoLahUI.h"
#include "DoLahCLI.h"


int main(int argc, char *argv[])
{
    if (argc < 2) {
        QApplication app(argc, argv);
        DoLah::DoLahUI window;
        window.show();
        FreeConsole();
        return app.exec();
    } else {
        startConsole();
        return 0;
    }
}

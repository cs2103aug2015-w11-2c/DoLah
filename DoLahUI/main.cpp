//@@collate A0114391M
#include "DoLahUI.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    DoLah::DoLahUI window;
    window.show();
    FreeConsole();
    return app.exec();
}

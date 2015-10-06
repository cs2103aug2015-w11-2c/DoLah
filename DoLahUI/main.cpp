#include "DoLahUI.h"

namespace DoLah {

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
            startConsole();
            return 0;
        }
    }

}
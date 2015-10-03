#include "DoLahUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DoLahUI window;
    window.show();
    return app.exec();
}

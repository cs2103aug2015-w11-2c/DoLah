#include "SettingsWindow.h"


namespace DoLah {
    SettingsWindow::SettingsWindow() {
        this->resize(350, 570);
        this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    }


    SettingsWindow::~SettingsWindow()
    {
    }

}
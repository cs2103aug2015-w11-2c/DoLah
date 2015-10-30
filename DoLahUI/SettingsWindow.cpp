#include "SettingsWindow.h"


namespace DoLah {
    SettingsWindow::SettingsWindow(QMainWindow *window) {
        this->mainWin = window;
        this->resize(400, 350);
        this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        themeOptions();
    }

    SettingsWindow::~SettingsWindow()
    {
    }

    void SettingsWindow::themeOptions() {
        themeSelection = new QComboBox(this);
        themeSelection->addItem("Default");
        themeSelection->addItem("Windows 10");
        themeSelection->setGeometry(QRect(50, 100, 300, 20));
        connect(themeSelection, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTheme(int)));
    }

    void SettingsWindow::changeTheme(int index) {
        if (index == 0) {
            QFile stylesheet("stylesheet.qss");
            if (stylesheet.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                mainWin->setStyleSheet(stylesheet.readAll());
                stylesheet.close();
            }
            themeSelection->setCurrentIndex(0);
        }
        else if (index == 1) {
            QFile stylesheet("night_stylesheet.qss");
            if (stylesheet.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                mainWin->setStyleSheet(stylesheet.readAll());
                stylesheet.close();
            }
            themeSelection->setCurrentIndex(1);
        }
    }
}
#include "SettingsWindow.h"


namespace DoLah {
    SettingsWindow::SettingsWindow(QMainWindow *window) {
        this->window = window;
        this->resize(400, 350);
        this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        themeOptions();
    }

    SettingsWindow::~SettingsWindow()
    {
    }

    void SettingsWindow::themeOptions() {
        themeSelect = new QComboBox(this);
        themeSelect->addItem("Default");
        themeSelect->addItem("Windows 10");
        themeSelect->setGeometry(QRect(50, 100, 300, 20));
        connect(themeSelect, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTheme(int)));
    }

    void SettingsWindow::changeTheme(int index) {
        if (index == 0) {
            QFile stylesheet("stylesheet.qss");
            if (stylesheet.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                window->setStyleSheet(stylesheet.readAll());
                stylesheet.close();
            }
            themeSelect->setCurrentIndex(0);
        }
        else if (index == 1) {
            QFile stylesheet("night_stylesheet.qss");
            if (stylesheet.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                window->setStyleSheet(stylesheet.readAll());
                stylesheet.close();
            }
            themeSelect->setCurrentIndex(1);
        }
    }
}
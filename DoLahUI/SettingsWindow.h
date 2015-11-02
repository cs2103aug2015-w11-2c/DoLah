#pragma once
#include "MenuLabel.h"

#include <QtWidgets/QDialog>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QMainWindow>
#include <QFile>

namespace DoLah {
    class SettingsWindow :
        public QDialog
    {
        Q_OBJECT

    public:
        SettingsWindow(QMainWindow * parent);
        ~SettingsWindow();

        MenuLabel *exitButton;

    private slots:
        void changeTheme(int);

    private:
        QComboBox *themeSelection;
        QMainWindow *mainWin;
        void themeOptions();
        void readAndSetStyleSheet(const char*);
    };
}

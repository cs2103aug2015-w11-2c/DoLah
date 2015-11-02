#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets/QComboBox>
#include <QMainWindow>
#include <QFile>

namespace DoLah {
    class SettingsWindow :
        public QDialog
    {
        Q_OBJECT

    public:
        SettingsWindow(QMainWindow*);
        ~SettingsWindow();

    private slots:
        void changeTheme(int);

    private:
        QComboBox *themeSelection;
        QMainWindow *mainWin;
        void themeOptions();
        void readAndSetStyleSheet(const char*);
    };
}

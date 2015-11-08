#pragma once
#include "MenuLabel.h"

#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QPushButton>
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

        QFileDialog *fileBrowser;
        MenuLabel *exitButton;
        QDialogButtonBox *buttonBox;
        QPushButton *browseButton;

    signals:
        void applySettings(QString);

    protected:
        void keyPressEvent(QKeyEvent*);

    private slots:
        void browseLocation();
        void changeTheme(int);
        void applyChanges();
        void cancelChanges();

    private:
        int originalTheme;
        QString originalLocation;
        QString selectedLocation;
        QLineEdit *storageLocationBox;
        QComboBox *themeSelection;
        QMainWindow *mainWin;
        void storageSettings();
        void themeOptions();
        void readAndSetStyleSheet(const char*);
    };
}

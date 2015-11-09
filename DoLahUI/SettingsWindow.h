#pragma once
#include "MenuLabel.h"
#include "Config/ConfigurationManager.h"

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
        QLineEdit *storageLocationBox; /**< Where user-selected storage location is displayed*/
        MenuLabel *exitButton;
        QDialogButtonBox *buttonBox;
        QPushButton *browseButton;

    signals:
        void applyStorageSettings(QString); /**< This signal is emitted when the user presses the ok button in the EasyEdit window*/

    protected:
        void keyPressEvent(QKeyEvent*); /**< Reimplemented from QWidget::keyPressEvent() */

    private slots:
        void browseLocation(); /**< Opens fileBrowser, then gets and stores the user-selected location */
        void changeTheme(int); /**< Changes the theme according to user selection */
        void applyChanges();
        void cancelChanges();

    private:
        int originalTheme;
        QFileDialog *fileBrowser;
        QString originalLocation;
        QString selectedLocation;
        QComboBox *themeSelection;
        QMainWindow *mainWin;
        void storageSettings();
        void themeOptions(); /**< Initializes the drop down menu allowing theme selection */
        /**
        * Reads stylesheet from a QSS file and sets it as the main window stylesheet
        * @param qss file name of the QSS stylesheet to be loaded
        */
        void readAndSetStyleSheet(const char*);
    };
}

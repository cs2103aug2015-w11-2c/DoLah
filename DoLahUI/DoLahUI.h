#ifndef DOLAHUI_H
#define DOLAHUI_H

#include "DoLahClient.h"
#include "UITaskBox.h"
#include "MenuLabel.h"
#include "DisplayArea.h"
#include "InputBox.h"
#include "HelpWindow.h"
#include "SettingsWindow.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QSizePolicy>
#include <QFile>
#include <QMouseEvent>
#include <QScrollBar>

namespace DoLah {
    /**
    * \brief Setup the main window for the DoLah application.
    *
    * The main window is made up of 3 main components: the menu, DisplayArea, and InputBox.
    */
    class DoLahUI : public QMainWindow
    {
        Q_OBJECT

    public:
        DoLahUI(QWidget *parent = 0);
        ~DoLahUI();

        QFile stylesheet;
        QWidget *centralWidget; /**< Main widget of the main window. Classes that are to be displayed in the main window should set this as parent*/

        QWidget *menu; /**< QWidget containing the menu*/
        QHBoxLayout *menuLayout; /**< Layout to be applied to menu*/
        MenuLabel *homeButton;
        MenuLabel *doneButton;
        MenuLabel *searchButton;
        MenuLabel *helpButton;
        MenuLabel *settingsButton;
        MenuLabel *exitButton;

        DisplayArea *viewPort; /**< QWidget containing the display area*/
        QStackedWidget *tabOrganizer; /**< Manages the different task views*/
        QVBoxLayout *home; /**< Layout to be applied to default view*/
        QVBoxLayout *done; /**< Layout to be applied to done tasks menu*/
        QVBoxLayout *search; /**< Layout to be applied to search results view*/

        QLabel *message; /**< Message displaying program response to user input*/
        InputBox *lineEdit; /**< Input area where user input is entered*/

        HelpWindow *helpWindow;
        SettingsWindow *settingsWindow;

    protected:
        void mousePressEvent(QMouseEvent*); /**< Reimplemented from QWidget::mousePressEvent() */
        void mouseMoveEvent(QMouseEvent*); /**< Reimplemented from QWidget::mouseMoveEvent() */
        void keyPressEvent(QKeyEvent*); /**< Reimplemented from QWidget::keyPressEvent() */

    private slots:
        void handleUserInput(); /**< Handles the input in InputBox entered by the user */
        void handleEasyEdit(int, QString); /**< Handles the input in EasyEdit entered by the user */
        void goToHome(); /**< Sets the display area to show the default view*/
        void goToDone(); /**< Sets the display area to show the done tasks view*/
        void goToSearch(); /**< Sets the display area to show the search results view*/
        void goToHelp(); /**< Opens the help window*/
        void goToSettings(); /**< Opens the settings window*/
        void setStorageLocation(QString); /**< Sets the storage location for the file containing tasks data*/
        void menuExit(); /**< Quits the program*/
        void updateMenu(int); /**< Changes the appearance of the menu's tabs according to the active view*/

    private:
        void setupUI();
        void retranslateUI();
        void initMenu();
        void initDisplayArea();
        void initInputArea();
        void clearMenuStyles(); /**< Clears the tab indication appearance of the menu buttons*/
        /**
        * Creates a UITaskBox that displays a task
        * @param page the layout to where the created task box is added to
        * @param index index of the task
        * @param task AbstractTask to be added and displayed
        */
        void createTaskBox(QVBoxLayout*, int, AbstractTask*);
        void loadTasks(); /**< Loads tasks in all views*/
        void refreshTasks(); /**< Refreshes all views*/
        /**
        * Clears all tasks in the view
        * @param page the layout to be cleared
        */
        void flushPage(QVBoxLayout*);

        DoLah::DoLahClient appClient;
        QPoint dragPosition;
    };
}
#endif // DOLAHUI_H
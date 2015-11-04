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
#include <QtWidgets/QAction>
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
    class DoLahUI : public QMainWindow
    {
        Q_OBJECT

    public:
        DoLahUI(QWidget *parent = 0);
        ~DoLahUI();

        QFile stylesheet;
        QWidget *centralWidget;

        QWidget *menu;
        QHBoxLayout *menuLayout;
        MenuLabel *homeButton;
        MenuLabel *doneButton;
        MenuLabel *searchButton;
        MenuLabel *helpButton;
        MenuLabel *settingsButton;
        MenuLabel *exitButton;

        DisplayArea *viewPort;
        QStackedWidget *tabOrganizer;
        QVBoxLayout *home;
        QVBoxLayout *done;
        QVBoxLayout *search;

        QLabel *message;
        InputBox *lineEdit;

        HelpWindow *helpWindow;
        SettingsWindow *settingsWindow;

    protected:
        void mousePressEvent(QMouseEvent*);
        void mouseMoveEvent(QMouseEvent*);
        void keyPressEvent(QKeyEvent*);

    private slots:
        void handleUserInput();
        void menuExit();
        void updateMenu(int);
        void goToHome();
        void goToDone();
        void goToSearch();
        void goToHelp();
        void goToSettings();

    private:
        void setupUI();
        void retranslateUI();
        void initMenu();
        void initDisplayArea();
        void initInputArea();
        void clearMenuStyles();
        void createTaskBox(QVBoxLayout*, int, AbstractTask*);
        void loadTasks();
        void refreshTasks();
        void flushPage(QVBoxLayout*);

        DoLah::DoLahClient appClient;
        QPoint dragPosition;
    };
}
#endif // DOLAHUI_H
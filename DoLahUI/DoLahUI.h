#ifndef DOLAHUI_H
#define DOLAHUI_H

#include "DoLahClient.h"
#include "UITaskBox.h"
#include "MenuLabel.h"
#include "DisplayArea.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>
#include <QtWidgets/QSizePolicy>
#include <QtWidgets/QStackedWidget>
#include <QFile>
#include <QMouseEvent>

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
        MenuLabel *settingsButton;
        MenuLabel *exitButton;

        DisplayArea *viewPort;
        QStackedWidget *tabOrganizer;
        QVBoxLayout *home;
        QVBoxLayout *sort;
        QVBoxLayout *tags;
        QVBoxLayout *done;

        QLabel *message;
        QLineEdit *lineEdit;

    protected:
        void mousePressEvent(QMouseEvent*);
        void mouseMoveEvent(QMouseEvent*);

    private slots:
        void handleUserInput();
        void menuExit();
        void changeTheme();
        void goToHome();
        void goToDone();

    private:
        void setupUI();
        void retranslateUI();
        void initMenu();
        void initDisplayArea();
        void initInputArea();
        void createTaskBox(QVBoxLayout*, int, AbstractTask*);
        void loadTasks();
        void refreshTasks();
        void flushPage(QVBoxLayout*);

        DoLah::DoLahClient appClient;
        QPoint dragPosition;
        int themecounter = 0;
    };
}
#endif // DOLAHUI_H
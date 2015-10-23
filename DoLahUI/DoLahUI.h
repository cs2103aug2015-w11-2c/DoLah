#ifndef DOLAHUI_H
#define DOLAHUI_H

#include "DoLahClient.h"
#include "UITaskBox.h"
#include "MenuLabel.h"

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
        MenuLabel *exitButton;
        MenuLabel *settingsButton;

        QScrollArea *scrollArea;
        QWidget *tasksContainer;
        QVBoxLayout *tasksLayout;

        QLabel *message;
        QLineEdit *lineEdit;

    protected:
        void mousePressEvent(QMouseEvent*);
        void mouseMoveEvent(QMouseEvent*);

    private slots:
        void handleUserInput();
        void menuExit();
        void changeTheme();

    private:
        void setupUI();
        void retranslateUI();
        void initMenu();
        void initDisplayArea();
        void initInputArea();
        void createTaskBox(int, AbstractTask*);
        void loadTasks();
        void refreshTasks();

        DoLah::DoLahClient appClient;
        QPoint dragPosition;
        int themecounter = 0;
    };
}
#endif // DOLAHUI_H
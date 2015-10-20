#ifndef DOLAHUI_H
#define DOLAHUI_H

#include "DoLahClient.h"
#include "UITaskBox.h"

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
#include <QtWidgets/QTextBrowser>
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

        QHBoxLayout *menu;

        QScrollArea *scrollArea;
        QWidget *tasksContainer;
        QVBoxLayout *tasksLayout;
        QTextBrowser *taskBox;

        QLabel *message;
        QLineEdit *lineEdit;

    private slots:
        void handleUserInput();

    private:
        void setupUI();
        void retranslateUI();
        void mousePressEvent(QMouseEvent*);
        void mouseMoveEvent(QMouseEvent*);
        void initMenu();
        void initDisplayArea();
        void initInputArea();
        void createTaskBox(AbstractTask*);
        void loadTasks();
        void refreshTasks();

        DoLah::DoLahClient appClient;
        QPoint dragPosition;
    };
}
#endif // DOLAHUI_H
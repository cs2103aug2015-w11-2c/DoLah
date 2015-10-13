#ifndef DOLAHUI_H
#define DOLAHUI_H

#include "DoLahClient.h"

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
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QSizePolicy>

namespace DoLah {
    class DoLahUI : public QMainWindow
    {
        Q_OBJECT

    public:
        DoLahUI(QWidget *parent = 0);
        ~DoLahUI();

        QWidget *centralWidget;
        QScrollArea *scrollArea;
        QWidget *tasksContainer;
        QVBoxLayout *tasksLayout;
        QTextBrowser *taskBox;
        QTextBrowser *taskBox1;
        QTextBrowser *taskBox2;
        QTextBrowser *taskBox3;
        QTextBrowser *taskBox4;
        QTextBrowser *taskBox5;
        QLineEdit *lineEdit;

    private:
        void setupUI();
        void retranslateUI();
        void initDisplayArea();
        void initInputArea();
        void createTaskBox(AbstractTask*);

        DoLah::DoLahClient appClient;
    };
}
#endif // DOLAHUI_H
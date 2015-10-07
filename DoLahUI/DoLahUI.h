#ifndef DOLAHUI_H
#define DOLAHUI_H

#include "..\DoLah\DoLahClient.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

namespace DoLah {
    class DoLahUI : public QMainWindow
    {
        Q_OBJECT

    public:
        DoLahUI(QWidget *parent = 0);
        ~DoLahUI();

        QWidget *centralWidget;
        QScrollArea *scrollArea;
        QLabel *tasksLabel;
        QLineEdit *lineEdit;
        QPushButton *pushButton;

    private:
        void setupUI();
        void retranslateUI();
        void initDisplayArea();
        void initInputArea();
        //void eventHandler();
    };

    DoLahClient appClient;

    // Console Mode functions
    void startConsole();
}
#endif // DOLAHUI_H
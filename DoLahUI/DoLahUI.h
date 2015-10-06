#ifndef DOLAHUI_H
#define DOLAHUI_H

//#include "..\DoLah\DoLahClient.h"

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
    //DoLahClient appClient;

    void setupUI();
    void retranslateUI();
    void initDisplayArea();
};

#endif // DOLAHUI_H

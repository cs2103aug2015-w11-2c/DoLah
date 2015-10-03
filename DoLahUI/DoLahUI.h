#ifndef DOLAHUI_H
#define DOLAHUI_H

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
    QWidget *scrollAreaWidgetContents;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

private:
    void setupUi();
    void retranslateUi();
};

#endif // DOLAHUI_H

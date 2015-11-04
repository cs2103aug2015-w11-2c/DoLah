#pragma once
#include "MenuLabel.h"

#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QStackedWidget>
#include <QMouseEvent>

namespace DoLah {
    class HelpWindow :
        public QDialog
    {
        Q_OBJECT

    public:
        HelpWindow(QWidget * parent = 0, Qt::WindowFlags f = 0);
        ~HelpWindow();

        QLabel *bglabel;
        MenuLabel *exitButton;
        QWidget *navi;
        QVBoxLayout *navilayout;
        MenuLabel *nav_basic;
        QLabel *page_basic;
        MenuLabel *nav_add;
        QLabel *page_add;
        MenuLabel *nav_commands;
        QLabel *page_commands;
        MenuLabel *nav_datetime;
        QLabel *page_datetime;
        MenuLabel *nav_keyboard;
        QLabel *page_keyboard;
        MenuLabel *nav_other;
        QLabel *page_other;
        QStackedWidget *helpcontents;

    protected:
        void mousePressEvent(QMouseEvent*);
        void mouseMoveEvent(QMouseEvent*);
        void keyPressEvent(QKeyEvent*);

    private slots:
        void goToBasic();
        void goToAdd();
        void goToTypes();
        void goToDateTime();
        void goToCommands();
        void goToKeyboard();
        void goToOther();
        void updateNav(int);

    private:
        void initNavi();
        void addNaviLabel(QLabel*, QString);
        void clearStyles();
        QPoint dragPosition;
    };
}
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

        QLabel *bgLabel; /**< Holds the background image of the help window*/
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
        MenuLabel *nav_about;
        QLabel *page_about;
        QStackedWidget *helpcontents;

    protected:
        void mousePressEvent(QMouseEvent*); /**< Reimplemented from QWidget::mousePressEvent() */
        void mouseMoveEvent(QMouseEvent*); /**< Reimplemented from QWidget::mouseMoveEvent() */
        void keyPressEvent(QKeyEvent*); /**< Reimplemented from QWidget::keyPressEvent() */

    private slots:
        void goToBasic();
        void goToAdd();
        void goToDateTime();
        void goToCommands();
        void goToKeyboard();
        void goToOther();
        void goToAbout();
        void updateNav(int); /**< Changes the appearance of the navigation according to the active page*/

    private:
        void initNavi();
        /**
        * Adds a label with the desired text to the navigation
        * @param label Label to be added
        * @param text Text of the label
        */
        void addNaviLabel(QLabel*, QString);
        void clearStyles(); /**< Clears the navigation page indication*/
        void initContents();
        void initPage(QLabel*, QString);
        QPoint dragPosition;
    };
}

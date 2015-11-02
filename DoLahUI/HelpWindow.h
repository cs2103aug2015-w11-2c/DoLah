#pragma once
#include "MenuLabel.h"

#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
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

    protected:
        void mousePressEvent(QMouseEvent*);
        void mouseMoveEvent(QMouseEvent*);

    private:

        QPoint dragPosition;
    };
}

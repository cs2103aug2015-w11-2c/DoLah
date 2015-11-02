#pragma once
#include <QtWidgets/QLabel>
#include <QtWidgets/QApplication>
#include <QMouseEvent>

namespace DoLah {
    class MenuLabel : public QLabel
    {
        Q_OBJECT

    public:
        MenuLabel(QWidget *parent = 0);
        ~MenuLabel();

    signals:
        void clicked();

    protected:
        void mousePressEvent(QMouseEvent*);
        void mouseMoveEvent(QMouseEvent*);

    };

}

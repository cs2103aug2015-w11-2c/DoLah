#pragma once
#include <QtWidgets/QLabel>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QMouseEvent>

namespace DoLah {
    class MenuLabel : public QLabel
    {
        Q_OBJECT

    public:
        MenuLabel();
        ~MenuLabel();

    signals:
        void clicked();

    private:
        QPoint dragPosition;

    protected:
        void mousePressEvent(QMouseEvent*);
        void mouseMoveEvent(QMouseEvent*);

    };

}

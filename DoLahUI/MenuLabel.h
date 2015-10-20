#pragma once
#include <QtWidgets/QLabel>

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

    protected:
        void mousePressEvent(QMouseEvent*);

    };

}

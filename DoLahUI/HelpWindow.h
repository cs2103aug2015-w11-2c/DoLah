#pragma once
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
        HelpWindow();
        ~HelpWindow();

    protected:
        void mousePressEvent(QMouseEvent*);
        void mouseMoveEvent(QMouseEvent*);

    private:

        QPoint dragPosition;
    };
}

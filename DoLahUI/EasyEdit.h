#pragma once

#include "MenuLabel.h"
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QDialogButtonBox>
#include <QMouseEvent>

namespace DoLah {
    class EasyEdit :
        public QDialog
    {
        Q_OBJECT

    public:
        EasyEdit(QWidget * parent = 0, Qt::WindowFlags f = 0);
        ~EasyEdit();

        MenuLabel *exitButton;
        QLineEdit *editarea;
        QDialogButtonBox *buttonBox;

    protected:
        void mousePressEvent(QMouseEvent*);
        void mouseMoveEvent(QMouseEvent*);

    private:
        QPoint dragPosition;
    };

}
//@@author A0114391M
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
        QLabel *description;
        QLineEdit *editArea; /**< Input area where user can edit task*/
        QDialogButtonBox *buttonBox;

    protected:
        void mousePressEvent(QMouseEvent*); /**< Reimplemented from QWidget::mousePressEvent() */
        void mouseMoveEvent(QMouseEvent*); /**< Reimplemented from QWidget::mouseMoveEvent() */

    private:
        QPoint dragPosition;
    };

}

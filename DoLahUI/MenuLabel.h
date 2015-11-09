//@@collate A0114391M
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
        void clicked(); /**< This signal is emitted when the user clicks on the label */

    protected:
        void mousePressEvent(QMouseEvent*); /**< Reimplemented from QWidget::mousePressEvent() */
        void mouseMoveEvent(QMouseEvent*); /**< Reimplemented from QWidget::mouseMoveEvent() */

    };

}

#include "MenuLabel.h"


namespace DoLah {
    MenuLabel::MenuLabel() {
        this->setMinimumHeight(65);
    }


    MenuLabel::~MenuLabel() {

    }

    void MenuLabel::mousePressEvent(QMouseEvent* event) {
        emit clicked();
        if (event->button() == Qt::LeftButton) {
            event->accept();
        }
    }

    void MenuLabel::mouseMoveEvent(QMouseEvent *event) {
        if (event->buttons() & Qt::LeftButton) {
            event->accept();
        }
    }

}
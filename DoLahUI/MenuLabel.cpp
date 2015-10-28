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
            //dragPosition = event->globalPos() - static_cast<QMainWindow*>((parent())->parent()->parent())->frameGeometry().topLeft();
            event->accept();
        }
    }

    void MenuLabel::mouseMoveEvent(QMouseEvent *event) {
        if (event->buttons() & Qt::LeftButton) {
            //static_cast<QMainWindow*>((parent())->parent()->parent())->move(event->globalPos() - dragPosition);
            event->accept();
        }
    }

}
#include "MenuLabel.h"


namespace DoLah {
    MenuLabel::MenuLabel(QWidget *parent)
        : QLabel(parent) {
        this->setMinimumHeight(65);
        this->setObjectName(QStringLiteral("menuButton"));
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
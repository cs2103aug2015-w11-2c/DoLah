#include "MenuLabel.h"


namespace DoLah {
    MenuLabel::MenuLabel() {
        this->setMinimumHeight(65);
    }


    MenuLabel::~MenuLabel() {

    }

    void MenuLabel::mousePressEvent(QMouseEvent* event) {
        emit clicked();
    }

}
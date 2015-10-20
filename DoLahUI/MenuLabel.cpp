#include "MenuLabel.h"


namespace DoLah {
    MenuLabel::MenuLabel() {

    }


    MenuLabel::~MenuLabel() {

    }

    void MenuLabel::mousePressEvent(QMouseEvent* event) {
        emit clicked();
    }

}
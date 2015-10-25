#include "HelpWindow.h"

namespace DoLah {
    HelpWindow::HelpWindow() {
        this->resize(350, 570);
        this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        //QVBoxLayout *layout = new QVBoxLayout;
        QLabel *bglabel = new QLabel(this);
        QPixmap background("helpwindow.jpg");
        bglabel->setGeometry(QRect(0, 0, 350, 570));
        bglabel->setPixmap(background);
    }


    HelpWindow::~HelpWindow() {
    }

    void HelpWindow::mousePressEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }

    void HelpWindow::mouseMoveEvent(QMouseEvent *event) {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - dragPosition);
            event->accept();
        }
    }
}
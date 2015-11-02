#include "HelpWindow.h"

namespace DoLah {
    HelpWindow::HelpWindow(QWidget * parent, Qt::WindowFlags f)
        : QDialog(parent)
    {
        this->resize(350, 570);
        this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::Dialog);

        bglabel = new QLabel(this);
        QPixmap background("images/helpwindow.jpg");
        bglabel->setGeometry(QRect(0, 0, 350, 570));
        bglabel->setPixmap(background);

        exitButton = new MenuLabel(this);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        QPixmap exitIcon("images/dialog_exit.png");
        exitButton->setPixmap(exitIcon);
        exitButton->setGeometry(QRect(320, 0, 20, 20));
        QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(reject()));
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
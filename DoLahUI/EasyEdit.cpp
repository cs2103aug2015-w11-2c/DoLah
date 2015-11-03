#include "EasyEdit.h"


namespace DoLah {
    EasyEdit::EasyEdit(QWidget * parent, Qt::WindowFlags f)
        : QDialog(parent)
    {
        this->resize(350, 200);

        exitButton = new MenuLabel(this);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        QPixmap exitIcon("images/dialog_exit.png");
        exitButton->setPixmap(exitIcon);
        exitButton->setGeometry(QRect(320, 0, 20, 20));
        QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(reject()));
    }

    EasyEdit::~EasyEdit() { }

    void EasyEdit::mousePressEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }

    void EasyEdit::mouseMoveEvent(QMouseEvent *event) {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - dragPosition);
            event->accept();
        }
    }

}
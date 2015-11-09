#include "EasyEdit.h"


namespace DoLah {
    EasyEdit::EasyEdit(QWidget * parent, Qt::WindowFlags f)
        : QDialog(parent)
    {
        this->resize(450, 150);
        this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::Dialog);

        exitButton = new MenuLabel(this);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        QPixmap exitIcon("images/dialog_exit.png");
        exitButton->setPixmap(exitIcon);
        exitButton->setGeometry(QRect(420, 0, 20, 20));
        QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(reject()));

        description = new QLabel(this);
        description->setGeometry(QRect(25, 40, 370, 20));

        editArea = new QLineEdit(this);
        editArea->setGeometry(QRect(25, 60, 370, 20));
        editArea->setFocus();

        buttonBox = new QDialogButtonBox(this);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(0, 100, 450, 23));
        buttonBox->setCenterButtons(true);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
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
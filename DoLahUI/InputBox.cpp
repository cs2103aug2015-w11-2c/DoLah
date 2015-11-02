#include "InputBox.h"

namespace DoLah {
    InputBox::InputBox(QWidget *parent)
        : QLineEdit(parent)
    {
    }


    InputBox::~InputBox()
    {
    }

    void InputBox::keyPressEvent(QKeyEvent *event) {
        if (event->key() == Qt::Key_Up) {
            if (!commandstack_up.empty()) {
                std::string prev = commandstack_up.top();
                commandstack_down.push(prev);
                this->commandstack_up.pop();
                this->setText(QString::fromStdString(prev));
            }
        }
        else if (event->key() == Qt::Key_Down) {
            if (!commandstack_down.empty()) {
                std::string next = commandstack_down.top();
                commandstack_up.push(next);
                this->commandstack_down.pop();
                this->setText(QString::fromStdString(next));
            }
            else {
                this->clear();
            }
        }
        else {
            QLineEdit::keyPressEvent(event);
        }
    }

    void InputBox::arrangeStack() {
        while (!commandstack_down.empty()) {
            commandstack_up.push(commandstack_down.top());
            commandstack_down.pop();
        }
    }
}

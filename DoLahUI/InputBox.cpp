//@@collate A0114391M
#include "InputBox.h"

namespace DoLah {
    InputBox::InputBox(QWidget *parent)
        : QLineEdit(parent)
    {
    }

    InputBox::~InputBox() { }

    void InputBox::keyPressEvent(QKeyEvent *event) {
        if (event->key() == Qt::Key_Up) {
            if (!commandStackUp.empty()) {
                std::string prev = commandStackUp.top();
                commandStackDown.push(prev);
                this->commandStackUp.pop();
                this->setText(QString::fromStdString(prev));
            }
        }
        else if (event->key() == Qt::Key_Down) {
            if (!commandStackDown.empty()) {
                std::string next = commandStackDown.top();
                commandStackUp.push(next);
                this->commandStackDown.pop();
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
        while (!commandStackDown.empty()) {
            commandStackUp.push(commandStackDown.top());
            commandStackDown.pop();
        }
    }
}

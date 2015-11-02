#pragma once
#include <QtWidgets/QLineEdit>
#include <stack>
#include <QMouseEvent>

namespace DoLah {
    class InputBox :
        public QLineEdit
    {
        Q_OBJECT

    public:
        InputBox(QWidget *parent = 0);
        ~InputBox();
        void arrangeStack();

        std::stack<std::string> commandstack_up;
        std::stack<std::string> commandstack_down;

    protected:
        void keyPressEvent(QKeyEvent*);
    };

}

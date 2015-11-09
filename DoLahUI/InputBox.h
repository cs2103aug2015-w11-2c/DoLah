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

        std::stack<std::string> commandStackUp;
        std::stack<std::string> commandStackDown;

    protected:
        void keyPressEvent(QKeyEvent*);
    };

}

#pragma once
#include <QtWidgets/QLineEdit>

namespace DoLah {
    class InputBox :
        public QLineEdit
    {
        Q_OBJECT

    public:
        InputBox(QWidget *parent = 0);
        ~InputBox();
    };

}

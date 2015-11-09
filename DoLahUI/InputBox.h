//@@author A0114391M
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
        void arrangeStack(); /**< Moves all commands back up to commandstack_up */

        std::stack<std::string> commandStackUp; /**< Contains previous commands */
        std::stack<std::string> commandStackDown; /**< Contains previous commands that have been scrolled down */

    protected:
        void keyPressEvent(QKeyEvent*); /**< Reimplemented from QWidget::keyPressEvent() */
    };

}

#ifndef UITASKBOX_H
#define UITASKBOX_H

#include "DoLahClient.h"
#include <QtWidgets/QLabel>
#include <QMouseEvent>

namespace DoLah {
    class UITaskBox : public QLabel
    {
        Q_OBJECT

    public:
        UITaskBox(int, AbstractTask*);
        ~UITaskBox();
        QSize sizeHint() const;

    protected:
        /*void mouseDoubleClickEvent(QMouseEvent*);
        void mousePressEvent(QMouseEvent*);*/

    private:
        void dynamicCast(int, AbstractTask*);
    };

}

#endif // UITASKBOX_H
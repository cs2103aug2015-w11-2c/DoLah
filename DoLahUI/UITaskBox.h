#ifndef UITASKBOX_H
#define UITASKBOX_H

#include "DoLahClient.h"
#include "EasyEdit.h"
#include <QtWidgets/QLabel>
#include <QTextDocument>
#include <QMainWindow>
#include <QMouseEvent>

namespace DoLah {
    class UITaskBox : public QLabel
    {
        Q_OBJECT

    public:
        UITaskBox(int, AbstractTask*);
        ~UITaskBox();
        QSize sizeHint() const;

        EasyEdit *easyEdit;

    protected:
        void mouseDoubleClickEvent(QMouseEvent*);

    private:
        void dynamicCast(int, AbstractTask*);

        QString editabletext;
    };

}

#endif // UITASKBOX_H
#ifndef UITASKBOX_H
#define UITASKBOX_H

#include "DoLahClient.h"
#include "EasyEdit.h"

#include <QtWidgets/QAction>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenu>
#include <QTextDocument>
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

    signals:
        void confirmed(int, QString);

    protected:
        void mousePressEvent(QMouseEvent*);
        void mouseMoveEvent(QMouseEvent*);
        void mouseDoubleClickEvent(QMouseEvent*);

    private slots:
        void handleEasyEdit();

    private:
        void dynamicCast(int, AbstractTask*);
        void tidyDate(char*);

        QString editabletext;
        int index;
        AbstractTask *task;
    };

}

#endif // UITASKBOX_H
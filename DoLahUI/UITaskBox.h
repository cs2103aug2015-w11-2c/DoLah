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

        EasyEdit *easyedit;
        /*QMenu *contextMenu;*/

    signals:
        void confirmed(int, QString);
        void rightclicked(QPoint);
        //void setDone(QString, int);
        //void deleteThis(int);
        /*void setUndone(QString, int);*/

    protected:
        void mousePressEvent(QMouseEvent*);
        void mouseMoveEvent(QMouseEvent*);
        void mouseDoubleClickEvent(QMouseEvent*);

    private slots:
        void handleEasyEdit();
        //void openContextMenu(QPoint);
        //void menuEdit();
        //void menuDone();
        //void menuDelete();
        //void menuUndone();

    private:
        //void initContextMenu(bool);
        void dynamicCast(int, AbstractTask*);
        void tidyDate(char*);

        QString editabletext;
        int index;
        AbstractTask *task;
    };

}

#endif // UITASKBOX_H
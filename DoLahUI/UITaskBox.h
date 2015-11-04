#ifndef UITASKBOX_H
#define UITASKBOX_H

#include "DoLahClient.h"
#include "EasyEdit.h"

#include <QtWidgets/QLabel>
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

    signals:
        void confirmed(int, QString);

    protected:
        void mouseDoubleClickEvent(QMouseEvent*);

    private slots:
        void handleEdit();

    private:
        void dynamicCast(int, AbstractTask*);

        QString editabletext;
        int index;
    };

}

#endif // UITASKBOX_H
#ifndef UITASKBOX_H
#define UITASKBOX_H

#include "DoLahClient.h"
#include <QtWidgets/QTextBrowser>

namespace DoLah {
    class UITaskBox : public QTextBrowser
    {
        Q_OBJECT

    public:
        UITaskBox(int, AbstractTask*);
        ~UITaskBox();
        QSize sizeHint() const;
        void adjust();

    private:
        void dynamicCast(int, AbstractTask*);
    };

}

#endif // UITASKBOX_H
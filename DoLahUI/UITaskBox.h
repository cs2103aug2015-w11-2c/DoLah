#ifndef UITASKBOX_H
#define UITASKBOX_H

#include <QtWidgets/QTextBrowser>

namespace DoLah {
    class UITaskBox : public QTextBrowser
    {
        Q_OBJECT

    public:
        UITaskBox();
        ~UITaskBox();
        QSize sizeHint() const;
        void adjust();
    };

}

#endif // UITASKBOX_H
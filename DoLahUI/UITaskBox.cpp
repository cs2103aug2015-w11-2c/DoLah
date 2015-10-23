#include "UITaskBox.h"


namespace DoLah {
    UITaskBox::UITaskBox()
    {
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        //this->setFrameStyle(QFrame::NoFrame);
    }


    UITaskBox::~UITaskBox()
    {
    }

    QSize UITaskBox::sizeHint() const {
        return QSize(350, 20);
    }

    void UITaskBox::adjust() {
        // Generate taskbox without displaying it so I can get content height
        this->setAttribute(Qt::WA_DontShowOnScreen);
        this->show();
        this->setFixedHeight(this->document()->size().height() + 5);
    }

}
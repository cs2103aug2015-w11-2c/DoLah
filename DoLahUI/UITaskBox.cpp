#include "UITaskBox.h"


namespace DoLah {
    UITaskBox::UITaskBox()
    {
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setFixedHeight(40);
        //this->setFrameStyle(QFrame::NoFrame);
    }


    UITaskBox::~UITaskBox()
    {
    }

}
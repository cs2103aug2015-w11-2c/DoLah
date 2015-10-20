#include "UITaskBox.h"


namespace DoLah {
    UITaskBox::UITaskBox()
    {
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setFixedHeight(40);
        this->setSizeAdjustPolicy(SizeAdjustPolicy::AdjustToContents);
        this->setObjectName(QStringLiteral("UITaskBox"));
        //this->setFrameStyle(QFrame::NoFrame);
    }


    UITaskBox::~UITaskBox()
    {
    }

    QSize UITaskBox::sizeHint() const {
        return QSize(350, 40);
    }

}
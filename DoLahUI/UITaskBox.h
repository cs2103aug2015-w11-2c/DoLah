#pragma once
#include <QtWidgets/QTextBrowser>
//#include "C:\Qt\Qt5.5.0\5.5\msvc2013_64\include\QtWidgets\qtextbrowser.h"

namespace DoLah {
    class UITaskBox : public QTextBrowser
    {
        Q_OBJECT

    public:
        UITaskBox();
        ~UITaskBox();
    };

}
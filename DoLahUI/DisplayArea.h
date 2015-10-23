#pragma once
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>
#include <QtWidgets/QSizePolicy>
#include <QtWidgets/QStackedWidget>

namespace DoLah {
    class DisplayArea :
        public QScrollArea
    {
        Q_OBJECT

    public:
        DisplayArea(QWidget *parent = 0);
        ~DisplayArea();
        QStackedWidget *tabbedView;
        QVBoxLayout *homeLayout;
        QVBoxLayout *sortLayout;
        QVBoxLayout *tagsLayout;
        QVBoxLayout *doneLayout;

    private:
        QWidget *homePage;
        QWidget *sortPage;
        QWidget *tagsPage;
        QWidget *donePage;

        void initViewPort();
    };

}

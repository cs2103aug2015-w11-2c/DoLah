#include "UITaskBox.h"


namespace DoLah {
    UITaskBox::UITaskBox(int index, AbstractTask *task) {
        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        //this->setFrameStyle(QFrame::NoFrame);
        dynamicCast(index, task);
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

    void UITaskBox::dynamicCast(int index, AbstractTask *task) {
        std::string name = task->getName();
        QString tasktitle = "<font size=4><b>" + QString::number(index) + ". " + QString::fromStdString(name);

        if (FloatingTask *fTask = dynamic_cast<FloatingTask*>(task)) {
            this->setObjectName(QStringLiteral("Floating"));
            this->setText(tasktitle);
        }
        else if (DeadlineTask *dTask = dynamic_cast<DeadlineTask*>(task)) {
            this->setObjectName(QStringLiteral("Deadline"));
            char *deadline = asctime(&(dTask->getDueDate()));
            if (task->isDone()) {
                QString contents = tasktitle.append("</font><br><font size=3>" + QString(deadline));
                this->setText(contents);
            }
            else {
                QString contents = tasktitle.append("</font><br><font size=3><font color=#2fb6a7>" + QString(deadline));
                this->setText(contents);
            }
            
        }
        else if (EventTask *eTask = dynamic_cast<EventTask*>(task)) {
            this->setObjectName(QStringLiteral("Event"));
            char *start = asctime(&(eTask->getStartDate()));
            char *end = asctime(&(eTask->getEndDate()));
            if (task->isDone()) {
                QString contents = tasktitle.append("</font><br><font size=3>" + QString(start) + " to " + QString(end));
                this->setText(contents);
            }
            else {
                QString contents = tasktitle.append("</font><br><font size=3><font color=#2fb6a7>" + QString(start) + " to " + QString(end));
                this->setText(contents);
            }
        }
        if (task->isDone()) {
            this->setObjectName(QStringLiteral("Done"));
        }
    }

}
#include "UITaskBox.h"


namespace DoLah {
    UITaskBox::UITaskBox(int index, AbstractTask *task) {
        this->setWordWrap(true);
        this->setFrameStyle(QFrame::NoFrame);
        dynamicCast(index, task);
    }


    UITaskBox::~UITaskBox()
    {
    }

    QSize UITaskBox::sizeHint() const {
        return QSize(350, 300);
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
            char deadline[100];
            strftime(deadline, 100, "%a %e %b %Y %I:%M %p", &(dTask->getDueDate()));
            if (task->isDone()) {
                QString contents = tasktitle.append("</font><br><font size=3>" + QString(deadline));
                this->setText(contents);
            }
            else if (task->isExpired()) {
                QString contents = tasktitle.append("</font><br><font size=3><font color=#fc7370>" + QString(deadline));
                this->setText(contents);
            }
            else {
                QString contents = tasktitle.append("</font><br><font size=3><font color=#6270d6>" + QString(deadline));
                this->setText(contents);
            }
            
        }
        else if (EventTask *eTask = dynamic_cast<EventTask*>(task)) {
            this->setObjectName(QStringLiteral("Event"));
            char start[100];
            char end[100];
            strftime(start, 100, "%a %e %b %Y %I:%M %p", &(eTask->getStartDate()));
            strftime(end, 100, "%a %e %b %Y %I:%M %p", &(eTask->getEndDate()));
            if (task->isDone()) {
                QString contents = tasktitle.append("</font><br><font size=3>" + QString(start) + " to " + QString(end));
                this->setText(contents);
            }
            else if (task->isExpired()) {
                QString contents = tasktitle.append("</font><br><font size=3><font color=#fc7370>" + QString(start) + " to " + QString(end));
                this->setText(contents);
            }
            else {
                QString contents = tasktitle.append("</font><br><font size=3><font color=#6270d6>" + QString(start) + " to " + QString(end));
                this->setText(contents);
            }
        }
        if (task->isDone()) {
            this->setObjectName(QStringLiteral("Done"));
        }
        if (task->isExpired()) {
            this->setObjectName(QStringLiteral("Due"));
        }
    }

    void UITaskBox::mouseDoubleClickEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            this->setText("LOLOLOLOL");
        }
    }

}
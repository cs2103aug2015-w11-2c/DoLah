//@@author A0114391M
#include "UITaskBox.h"


namespace DoLah {
    UITaskBox::UITaskBox(int index, AbstractTask *task) {
        this->setWordWrap(true);
        this->setFrameStyle(QFrame::NoFrame);
        this->index = index;
        this->task = task;
        dynamicCast(index, task);
        easyEdit = new EasyEdit(this);
        QObject::connect(easyEdit->buttonBox, SIGNAL(accepted()), this, SLOT(handleEasyEdit()));

    }

    UITaskBox::~UITaskBox() { }

    QSize UITaskBox::sizeHint() const {
        return QSize(350, 300);
    }

    void UITaskBox::dynamicCast(int index, AbstractTask *task) {
        std::string name = task->getName();
        QString tasktitle = "<font size=4><b>" + QString::number(index) + ". " + QString::fromStdString(name);

        if (FloatingTask *fTask = dynamic_cast<FloatingTask*>(task)) {
            this->setObjectName(QStringLiteral("Floating"));
            this->setText(tasktitle);
            editabletext = QString::fromStdString(name);
        }
        else if (DeadlineTask *dTask = dynamic_cast<DeadlineTask*>(task)) {
            this->setObjectName(QStringLiteral("Deadline"));
            char deadline[100];
            strftime(deadline, 100, "%a %e %b %Y %I:%M%p", &(dTask->getDueDate()));
            tidyDate(deadline);
            editabletext = QString::fromStdString(name) + " by " + QString(deadline);
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
            strftime(start, 100, "%a %e %b %Y %I:%M%p", &(eTask->getStartDate()));
            strftime(end, 100, "%a %e %b %Y %I:%M%p", &(eTask->getEndDate()));
            tidyDate(start);
            tidyDate(end);
            editabletext = QString::fromStdString(name) + " from " + QString(start) + " to " + QString(end);
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
        if (task->isExpired()) {
            this->setObjectName(QStringLiteral("Due"));
        }
        if (task->isDone()) {
            this->setObjectName(QStringLiteral("Done"));
        }
    }

    void UITaskBox::tidyDate(char date[]) {
        if (isspace(date[4])) {
            for (int i = 4; i < 100; i++) {
                date[i] = date[i + 1];
            }
        }
    }

    //////////////////////////////////////////
    // OVERRIDING CLICK AND KEYBOARD INPUTS //
    //////////////////////////////////////////

    void UITaskBox::mousePressEvent(QMouseEvent *event) {
        event->ignore();
    }
    void UITaskBox::mouseMoveEvent(QMouseEvent *event) {
        event->ignore();
    }
    void UITaskBox::mouseDoubleClickEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            if (!task->isDone()) {
                easyEdit->editArea->setText(editabletext);
                QString temp = QString("Edit task ") + QString::number(index) + ":";
                easyEdit->description->setText(temp);
                easyEdit->exec();
            }
        }
    }

    //////////////////////////////////////////
    //                SLOTS                 //
    //////////////////////////////////////////

    void UITaskBox::handleEasyEdit() {
        if (!easyEdit->editArea->text().isEmpty()) {
            emit confirmed(index, easyEdit->editArea->text());
        }
        else {
            easyEdit->reject();
        }
    }
}

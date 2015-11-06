#include "UITaskBox.h"


namespace DoLah {
    UITaskBox::UITaskBox(int index, AbstractTask *task) {
        this->setWordWrap(true);
        this->setFrameStyle(QFrame::NoFrame);
        //this->setContextMenuPolicy(Qt::CustomContextMenu);
        this->index = index;
        this->task = task;
        dynamicCast(index, task);
        /*initContextMenu(task->isDone());
        QObject::connect(this, SIGNAL(rightclicked(QPoint)), this, SLOT(openContextMenu(QPoint)));*/
        easyedit = new EasyEdit(this);
        QObject::connect(easyedit->buttonBox, SIGNAL(accepted()), this, SLOT(handleEasyEdit()));

    }

    UITaskBox::~UITaskBox()
    {
    }

    QSize UITaskBox::sizeHint() const {
        return QSize(350, 300);
    }

    /*void UITaskBox::initContextMenu(bool done) {
        contextMenu = new QMenu(this);
        if (done) {
            contextMenu->addAction("Undone");
            QObject::connect(contextMenu->actions().at(0), SIGNAL(triggered()), this, SLOT(menuUndone()));
        }
        else {
            contextMenu->addAction("Edit");
            QObject::connect(contextMenu->actions().at(0), SIGNAL(triggered()), this, SLOT(menuEdit()));
            contextMenu->addAction("Done");
            QObject::connect(contextMenu->actions().at(1), SIGNAL(triggered()), this, SLOT(menuDone()));
            contextMenu->addAction("Delete");
            QObject::connect(contextMenu->actions().at(2), SIGNAL(triggered()), this, SLOT(menuDelete()));
        }
    }*/

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

    // Remove space padding from strftime %e
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
        if (event->button() == Qt::RightButton) {
            emit rightclicked(event->globalPos());
        }
        else {
            event->ignore();
        }
    }
    void UITaskBox::mouseMoveEvent(QMouseEvent *event) {
        event->ignore();
    }
    void UITaskBox::mouseDoubleClickEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            if (!task->isDone()) {
                easyedit->editarea->setText(editabletext);
                QString temp = QString("Edit task ") + QString::number(index) + ":";
                easyedit->description->setText(temp);
                easyedit->exec();
            }
        }
    }

    //////////////////////////////////////////
    //                SLOTS                 //
    //////////////////////////////////////////

    void UITaskBox::handleEasyEdit() {
        if (!easyedit->editarea->text().isEmpty()) {
            emit confirmed(index, easyedit->editarea->text());
        }
        else {
            easyedit->reject();
        }
    }

    //void UITaskBox::openContextMenu(QPoint pos) {
    //    contextMenu->exec(pos);
    //}

    //void UITaskBox::menuEdit() {
    //    easyedit->editarea->setText(editabletext);
    //    QString temp = QString("Edit task ") + QString::number(index) + ":";
    //    easyedit->description->setText(temp);
    //    easyedit->exec();
    //}
    //void UITaskBox::menuDone() {
    //    emit setDone(index);
    //}
    //void UITaskBox::menuDelete() {
    //    emit deleteThis(index);
    //}
    /*void UITaskBox::menuUndone() {
        emit setUndone(QString("undone "), index);
    }*/
}
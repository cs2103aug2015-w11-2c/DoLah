//@@collate A0114391M
#ifndef UITASKBOX_H
#define UITASKBOX_H

#include "DoLahClient.h"
#include "EasyEdit.h"

#include <QtWidgets/QAction>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenu>
#include <QTextDocument>
#include <QMouseEvent>

namespace DoLah {
    class UITaskBox : public QLabel
    {
        Q_OBJECT

    public:
        UITaskBox(int, AbstractTask*);
        ~UITaskBox();
        QSize sizeHint() const; /**< Reimplemented from QWidget::sizeHint() */

        EasyEdit *easyEdit;

    signals:
        void confirmed(int, QString); /**< This signal is emitted when the user presses the ok button in the EasyEdit window */

    protected:
        void mousePressEvent(QMouseEvent*); /**< Reimplemented from QWidget::mousePressEvent() */
        void mouseMoveEvent(QMouseEvent*); /**< Reimplemented from QWidget::mouseMoveEvent() */
        void mouseDoubleClickEvent(QMouseEvent*); /**< Reimplemented from QWidget::mouseDoubleClickEvent() */

    private slots:
        void handleEasyEdit(); /**< Handles what happens when user presses ok in easyedit */

    private:
        /**
        * Casts AbstractTask to either EventTask, DeadlineTask, or FloatingTask, formats and displays it in the UITaskBox
        * @param index index of the task
        * @param task AbstractTask to be casted and displayed
        */
        void dynamicCast(int, AbstractTask*);
        /**
        * Removes the extra space padding from strftime %e
        * @param date Date to be manipulated
        */
        void tidyDate(char*);

        QString editabletext;
        int index;
        AbstractTask *task;
    };

}

#endif // UITASKBOX_H

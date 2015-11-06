#include "HelpWindow.h"

namespace DoLah {
    HelpWindow::HelpWindow(QWidget * parent, Qt::WindowFlags f)
        : QDialog(parent)
    {
        this->resize(750, 500);
        this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::Dialog);
        this->setObjectName(QStringLiteral("helpwindow"));

        bglabel = new QLabel(this);
        QPixmap background("images/helpwindow.jpg");
        bglabel->setGeometry(QRect(0, 0, 308, 500));
        bglabel->setPixmap(background);

        initNavi();

        page_basic = new QLabel;
        QPixmap basicimg("images/help_basic.png");
        page_basic->setPixmap(basicimg);

        page_add = new QLabel;
        QPixmap addimg("images/help_add.png");
        page_add->setPixmap(addimg);

        page_commands = new QLabel;
        QPixmap commandsimg("images/help_commands.png");
        page_commands->setPixmap(commandsimg);

        page_datetime = new QLabel;
        QPixmap datetimeimg("images/help_datetime.png");
        page_datetime->setPixmap(datetimeimg);

        page_keyboard = new QLabel;
        QPixmap keyboardimg("images/help_keyboard.png");
        page_keyboard->setPixmap(keyboardimg);

        page_other = new QLabel;
        QPixmap otherimg("images/help_other.png");
        page_other->setPixmap(otherimg);

        page_about = new QLabel;
        QPixmap aboutimg("images/help_about.png");
        page_about->setPixmap(aboutimg);

        helpcontents = new QStackedWidget(this);
        helpcontents->setGeometry(QRect(278, 25, 450, 450));
        helpcontents->addWidget(page_basic);
        helpcontents->addWidget(page_add);
        helpcontents->addWidget(page_commands);
        helpcontents->addWidget(page_datetime);
        helpcontents->addWidget(page_keyboard);
        helpcontents->addWidget(page_other);
        helpcontents->addWidget(page_about);
        QObject::connect(helpcontents, SIGNAL(currentChanged(int)), this, SLOT(updateNav(int)));

        exitButton = new MenuLabel(this);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        QPixmap exitIcon("images/dialog_exit.png");
        exitButton->setPixmap(exitIcon);
        exitButton->setGeometry(QRect(720, 0, 20, 20));
        QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(reject()));
    }


    HelpWindow::~HelpWindow() {
    }

    void HelpWindow::initNavi() {
        navi = new QWidget(this);
        navi->setGeometry(28, 115, 200, 360);
        navilayout = new QVBoxLayout(navi);
        navilayout->setAlignment(Qt::AlignTop);
        navilayout->setSpacing(3);
        navilayout->setContentsMargins(0, 0, 0, 0);

        nav_basic = new MenuLabel;
        addNaviLabel(nav_basic, QString("Basic"));
        QObject::connect(nav_basic, SIGNAL(clicked()), this, SLOT(goToBasic()));
        nav_add = new MenuLabel;
        addNaviLabel(nav_add, QString("Adding Tasks"));
        QObject::connect(nav_add, SIGNAL(clicked()), this, SLOT(goToAdd()));
        nav_commands = new MenuLabel;
        addNaviLabel(nav_commands, QString("Commands"));
        QObject::connect(nav_commands, SIGNAL(clicked()), this, SLOT(goToCommands()));
        nav_datetime = new MenuLabel;
        addNaviLabel(nav_datetime, QString("Date/Time Format"));
        QObject::connect(nav_datetime, SIGNAL(clicked()), this, SLOT(goToDateTime()));
        nav_keyboard = new MenuLabel;
        addNaviLabel(nav_keyboard, QString("Keyboard Shortcuts"));
        QObject::connect(nav_keyboard, SIGNAL(clicked()), this, SLOT(goToKeyboard()));
        nav_other = new MenuLabel;
        addNaviLabel(nav_other, QString("Other Features"));
        QObject::connect(nav_other, SIGNAL(clicked()), this, SLOT(goToOther()));
        nav_about = new MenuLabel;
        addNaviLabel(nav_about, QString("About"));
        QObject::connect(nav_about, SIGNAL(clicked()), this, SLOT(goToAbout()));
        updateNav(0);

        QLabel *instructions = new QLabel("use PGUP/PGDN OR UP/DOWN ARROWS to navigate through the help pages");
        instructions->setWordWrap(true);
        instructions->setMinimumHeight(100);
        instructions->setAlignment(Qt::AlignCenter);
        navilayout->addWidget(instructions);
    }

    void HelpWindow::addNaviLabel(QLabel* label, QString text) {
        label->setText(text);
        label->setObjectName(QStringLiteral("helpnavi"));
        navilayout->addWidget(label);
    }

    void HelpWindow::mousePressEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }

    void HelpWindow::mouseMoveEvent(QMouseEvent *event) {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - dragPosition);
            event->accept();
        }
    }

    void HelpWindow::keyPressEvent(QKeyEvent *event) {
        if (event->key() == Qt::Key_PageUp || event->key() == Qt::Key_Up) {
            int index = helpcontents->currentIndex();
            if (index != 0) {
                helpcontents->setCurrentIndex(index - 1);
            }
        }
        else if (event->key() == Qt::Key_PageDown || event->key() == Qt::Key_Down) {
            int index = helpcontents->currentIndex();
            if (index != 6) {
                helpcontents->setCurrentIndex(index + 1);
            }
        }
        else {
            QDialog::keyPressEvent(event);
        }
    }

    void HelpWindow::clearStyles(){
        nav_basic->setStyleSheet("");
        nav_add->setStyleSheet("");
        nav_datetime->setStyleSheet("");
        nav_commands->setStyleSheet("");
        nav_keyboard->setStyleSheet("");
        nav_other->setStyleSheet("");
        nav_about->setStyleSheet("");
    }

    //////////////////////////////////////////
    //                SLOTS                 //
    //////////////////////////////////////////

    void HelpWindow::goToBasic() {
        helpcontents->setCurrentIndex(0);
    }
    void HelpWindow::goToAdd() {
        helpcontents->setCurrentIndex(1);
    }
    void HelpWindow::goToCommands() {
        helpcontents->setCurrentIndex(2);
    }
    void HelpWindow::goToDateTime() {
        helpcontents->setCurrentIndex(3);
    }
    void HelpWindow::goToKeyboard() {
        helpcontents->setCurrentIndex(4);
    }
    void HelpWindow::goToOther() {
        helpcontents->setCurrentIndex(5);
    }
    void HelpWindow::goToAbout() {
        helpcontents->setCurrentIndex(6);
    }

    void HelpWindow::updateNav(int index) {
        if (index == 0) {
            clearStyles();
            nav_basic->setStyleSheet("background-color: rgba(0, 0, 0, 0.5); color: white;");
        }
        else if (index == 1) {
            clearStyles();
            nav_add->setStyleSheet("background-color: rgba(0, 0, 0, 0.5); color: white;");
        }
        else if (index == 2) {
            clearStyles();
            nav_commands->setStyleSheet("background-color: rgba(0, 0, 0, 0.5); color: white;");
        }
        else if (index == 3) {
            clearStyles();
            nav_datetime->setStyleSheet("background-color: rgba(0, 0, 0, 0.5); color: white;");
        }
        else if (index == 4) {
            clearStyles();
            nav_keyboard->setStyleSheet("background-color: rgba(0, 0, 0, 0.5); color: white;");
        }
        else if (index == 5) {
            clearStyles();
            nav_other->setStyleSheet("background-color: rgba(0, 0, 0, 0.5); color: white;");
        }
        else {
            clearStyles();
            nav_about->setStyleSheet("background-color: rgba(0, 0, 0, 0.5); color: white;");
        }
    }
}
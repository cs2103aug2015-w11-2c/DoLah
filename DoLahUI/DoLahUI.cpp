#include "DoLahUI.h"

namespace DoLah {
    DoLahUI::DoLahUI(QWidget *parent)
        : QMainWindow(parent)
    {
        this->setupUI();
        QFile stylesheet("stylesheet.qss");
        if (stylesheet.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            setStyleSheet(stylesheet.readAll());
            stylesheet.close();
        }
    }

    DoLahUI::~DoLahUI() {
    }

    // MAIN WINDOW

    void DoLahUI::setupUI() {
        if (this->objectName().isEmpty()) {
            this->setObjectName(QStringLiteral("DoLahUIWindow"));
        }
        this->setFixedSize(350, 570);
        this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        centralWidget = new QWidget(this);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        this->setCentralWidget(centralWidget);
        initMenu();
        initDisplayArea();
        initInputArea();
        helpWindow = new HelpWindow();
        settingsWindow = new SettingsWindow(this);

        QMetaObject::connectSlotsByName(this);
    }
    //////////////////////////////////////////
    // OVERRIDING CLICK AND KEYBOARD INPUTS //
    //////////////////////////////////////////
    // HANDLE DRAGGING OF WINDOW

    void DoLahUI::mousePressEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }

    void DoLahUI::mouseMoveEvent(QMouseEvent *event) {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - dragPosition);
            event->accept();
        }
    }

    // HANDLE KEYPRESS EVENTS

    void DoLahUI::keyPressEvent(QKeyEvent *event) {
        if (event->key() == Qt::Key_Tab & event->modifiers() == Qt::ControlModifier) {
            int index = tabOrganizer->currentIndex();
            tabOrganizer->setCurrentIndex((index+1)%3);
        }
        else if (event->key() == Qt::Key_1 & event->modifiers() == Qt::ControlModifier) {
            goToHome();
        }
        else if (event->key() == Qt::Key_2 & event->modifiers() == Qt::ControlModifier) {
            goToDone();
        }
        else if (event->key() == Qt::Key_3 & event->modifiers() == Qt::ControlModifier) {
            goToSearch();
        }
        else if (event->key() == Qt::Key_PageUp) {
            // scroll up
        }
        else if (event->key() == Qt::Key_PageDown) {
            // scroll down
        }
        else {
            QMainWindow::keyPressEvent(event);
        }
    }

    //////////////////////////////////////////
    //            TOP MENU AREA             //
    //////////////////////////////////////////
    // INITIALIZATION

    void DoLahUI::initMenu() {
        menu = new QWidget(centralWidget);
        menu->setGeometry(QRect(0, 0, 350, 70));
        menuLayout = new QHBoxLayout(menu);
        menuLayout->setContentsMargins(5, 5, 5, 5);
        // DEFAULT VIEW
        homeButton = new MenuLabel;
        homeButton->setObjectName(QStringLiteral("home"));
        QPixmap homeIcon("home.png");
        homeButton->setPixmap(homeIcon);
        menuLayout->addWidget(homeButton);
        QObject::connect(homeButton, SIGNAL(clicked()), this, SLOT(goToHome()));
        // DONE TASKS VIEW
        doneButton = new MenuLabel;
        doneButton->setObjectName(QStringLiteral("done"));
        QPixmap doneIcon("done.png");
        doneButton->setPixmap(doneIcon);
        menuLayout->addWidget(doneButton);
        QObject::connect(doneButton, SIGNAL(clicked()), this, SLOT(goToDone()));
        // SEARCH RESULTS VIEW
        searchButton = new MenuLabel;
        searchButton->setObjectName(QStringLiteral("search"));
        QPixmap searchIcon("tags.png");
        searchButton->setPixmap(searchIcon);
        menuLayout->addWidget(searchButton);
        QObject::connect(searchButton, SIGNAL(clicked()), this, SLOT(goToSearch()));
        // HELP WINDOW
        helpButton = new MenuLabel;
        helpButton->setObjectName(QStringLiteral("help"));
        QPixmap helpIcon("help.png");
        helpButton->setPixmap(helpIcon);
        menuLayout->addWidget(helpButton);
        QObject::connect(helpButton, SIGNAL(clicked()), this, SLOT(goToHelp()));
        // SETTINGS
        settingsButton = new MenuLabel;
        settingsButton->setObjectName(QStringLiteral("settings"));
        QPixmap settingsIcon("settings.png");
        settingsButton->setPixmap(settingsIcon);
        menuLayout->addWidget(settingsButton);
        QObject::connect(settingsButton, SIGNAL(clicked()), this, SLOT(goToSettings()));
        // EXIT
        exitButton = new MenuLabel;
        exitButton->setObjectName(QStringLiteral("exitButton"));
        QPixmap exitIcon("exit.png");
        exitButton->setPixmap(exitIcon);
        menuLayout->addWidget(exitButton);
        QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(menuExit()));
    }

    //////////////////////////////////////////
    //            DISPLAY AREA              //
    //////////////////////////////////////////
    // INITIALIZATION

    void DoLahUI::initDisplayArea() {
        viewPort = new DisplayArea(centralWidget);
        tabOrganizer = viewPort->tabbedView;
        home = viewPort->homeLayout;
        done = viewPort->doneLayout;
        search = viewPort->searchLayout;
        loadTasks();
    }
    
    // METHODS TO UPDATE VIEWS

    void DoLahUI::loadTasks() {
        int i = 0;
        std::vector<AbstractTask*> taskList = (appClient.getCalendar()).getTaskList();
        for (i; i < taskList.size(); ++i) {
            createTaskBox(home, i+1, taskList[i]);
        }
        std::vector<AbstractTask*> doneList = appClient.getCalendar().getDoneList();
        for (int j = 0; j < doneList.size(); ++j) {
            createTaskBox(done, j+1, doneList[j]);
        }
        std::vector<AbstractTask*> searchedList = appClient.getCalendar().getSearchedTaskList();
        for (int k = 0; k < searchedList.size(); ++k) {
            createTaskBox(search, (searchedList[k])->getIndex()+1, searchedList[k]);
        }
    }

    void DoLahUI::refreshTasks() {
        flushPage(home);
        flushPage(done);
        flushPage(search);
        loadTasks();
    }

    void DoLahUI::flushPage(QVBoxLayout *page) {
        QLayoutItem* child;
        while ((child = page->takeAt(0)) != 0)
        {
            QWidget* widget = child->widget();
            if (widget)
            {
                delete child->widget();
                delete child;
            }
        }
    }
    
    void DoLahUI::createTaskBox(QVBoxLayout *page, int index, AbstractTask *task) {
        UITaskBox *tempTaskBox = new UITaskBox(index, task);
        page->addWidget(tempTaskBox, 0, 0);
    }

    //////////////////////////////////////////
    //              INPUT AREA              //
    //////////////////////////////////////////

    void DoLahUI::initInputArea() {
        message = new QLabel(centralWidget);
        message->setText("Enter a command:");
        message->setObjectName(QStringLiteral("message"));
        message->setGeometry(QRect(7, 520, 338, 20));

        lineEdit = new InputBox(centralWidget);
        lineEdit->setObjectName(QStringLiteral("inputarea"));
        lineEdit->setGeometry(QRect(5, 540, 340, 25));
        lineEdit->setFocus();

        // handles events when enter key is pressed
        QObject::connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(handleUserInput()));
        QObject::connect(lineEdit, SIGNAL(returnPressed()), lineEdit, SLOT(clear()));
    }

    //////////////////////////////////////////
    //                SLOTS                 //
    //////////////////////////////////////////

    void DoLahUI::handleUserInput() {
        QString input = lineEdit->text();
        std::string inputline = input.toStdString();
        lineEdit->arrangeStack();
        lineEdit->commandstack_up.push(inputline);
        if (inputline.length() != 0) {
            try {
                if (inputline == "help") {
                    goToHelp();
                }
                else if (inputline == "settings") {
                    goToSettings();
                }
                else if (inputline == "exit") {
                    menuExit();
                }
                else {
                    this->appClient.parseAndProcessCommand(inputline);
                    refreshTasks();
                    message->setText("Done. Enter next command:");
                }
            }
            catch (std::exception e) {
                QString text = QString(e.what());
                message->setText(text);
                refreshTasks();
            }
        }
        else {
            refreshTasks();
        }
    }

    void DoLahUI::goToHome() {
        tabOrganizer->setCurrentIndex(0);
    }

    void DoLahUI::goToDone() {
        tabOrganizer->setCurrentIndex(1);
    }

    void DoLahUI::goToSearch() {
        tabOrganizer->setCurrentIndex(2);
    }

    void DoLahUI::goToHelp() {
        helpWindow->exec();
    }

    void DoLahUI::goToSettings() {
        settingsWindow->exec();
    }

    void DoLahUI::menuExit() {
        exit(0);
    }

}
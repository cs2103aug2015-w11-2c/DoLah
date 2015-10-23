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

        this->resize(350, 570);
        this->setFixedSize(this->size());
        this->setWindowFlags(Qt::CustomizeWindowHint);
        this->setWindowFlags(Qt::FramelessWindowHint);
        centralWidget = new QWidget(this);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        initMenu();
        initDisplayArea();
        initInputArea();

        this->setCentralWidget(centralWidget);

        QMetaObject::connectSlotsByName(this);
    }

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

    // MENU

    void DoLahUI::initMenu() {
        menu = new QWidget(centralWidget);
        menu->setGeometry(QRect(0, 0, 350, 70));
        menuLayout = new QHBoxLayout(menu);
        menuLayout->setAlignment(Qt::AlignRight);
        menuLayout->setContentsMargins(5, 5, 5, 5);

        homeButton = new MenuLabel;
        homeButton->setObjectName(QStringLiteral("home"));
        homeButton->setText("HOME");
        menuLayout->addWidget(homeButton);
        QObject::connect(homeButton, SIGNAL(clicked()), this, SLOT(goToHome()));

        doneButton = new MenuLabel;
        doneButton->setObjectName(QStringLiteral("done"));
        doneButton->setText("DONE");
        menuLayout->addWidget(doneButton);
        QObject::connect(doneButton, SIGNAL(clicked()), this, SLOT(goToDone()));

        settingsButton = new MenuLabel;
        settingsButton->setObjectName(QStringLiteral("settings"));
        QPixmap settingsIcon("settings.png");
        settingsButton->setPixmap(settingsIcon);
        menuLayout->addWidget(settingsButton);
        QObject::connect(settingsButton, SIGNAL(clicked()), this, SLOT(changeTheme()));

        exitButton = new MenuLabel;
        exitButton->setObjectName(QStringLiteral("exitButton"));
        QPixmap exitIcon("exit.png");
        exitButton->setPixmap(exitIcon);
        menuLayout->addWidget(exitButton);
        QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(menuExit()));
    }

    // DISPLAY AREA

    void DoLahUI::initDisplayArea() {
        viewPort = new DisplayArea(centralWidget);
        tabOrganizer = viewPort->tabbedView;
        home = viewPort->homeLayout;
        done = viewPort->doneLayout;
        loadTasks();
    }

    void DoLahUI::loadTasks() {
        int i = 0;
        std::vector<AbstractTask*> taskList = (appClient.getCalendar()).getTaskList();
        for (i; i < taskList.size(); ++i) {
            createTaskBox(home, i, taskList[i]);
        }
        std::vector<AbstractTask*> doneList = appClient.getCalendar().getDoneList();
        for (int j = 0; j < doneList.size(); ++j) {
            createTaskBox(done, i+j, doneList[j]);
        }

    }

    void DoLahUI::refreshTasks() {
        flushPage(home);
        flushPage(done);
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
        std::string name = task->getName();
        QString tasktitle = "<font size=4><b>" + QString::number(index) + ". " + QString::fromStdString(name);
        UITaskBox *tempTaskBox = new UITaskBox();

        if (FloatingTask *fTask = dynamic_cast<FloatingTask*>(task)) {
            tempTaskBox->setObjectName(QStringLiteral("Floating"));
            tempTaskBox->setText(tasktitle);
        }
        else if (DeadlineTask *dTask = dynamic_cast<DeadlineTask*>(task)) {
            tempTaskBox->setObjectName(QStringLiteral("Deadline"));
            char *deadline = asctime(&(dTask->getDueDate()));
            QString contents = tasktitle.append("</font><br><font size=3><font color=#2fb6a7>" + QString(deadline));
            tempTaskBox->setText(contents);
        }
        else if (EventTask *eTask = dynamic_cast<EventTask*>(task)) {
            tempTaskBox->setObjectName(QStringLiteral("Event"));
            char *start = asctime(&(eTask->getStartDate()));
            char *end = asctime(&(eTask->getEndDate()));
            QString contents = tasktitle.append("</font><br><font size=3><font color=#2fb6a7>" + QString(start) + " to " + QString(end));
            tempTaskBox->setText(contents);
        }
        tempTaskBox->adjust();
        page->addWidget(tempTaskBox);
    }

    // INPUT AREA

    void DoLahUI::initInputArea() {
        message = new QLabel(centralWidget);
        message->setText("Enter a command:");
        message->setGeometry(QRect(7, 520, 338, 20));

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("User Input Area"));
        lineEdit->setGeometry(QRect(5, 540, 340, 25));
        lineEdit->setFocus();

        // handles events when enter key is pressed
        QObject::connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(handleUserInput()));
        QObject::connect(lineEdit, SIGNAL(returnPressed()), lineEdit, SLOT(clear()));
    }

    // SLOTS

    void DoLahUI::handleUserInput() {
        QString input = lineEdit->text();
        std::string inputline = input.toStdString();
        if (inputline.length() != 0) {
            try {
                this->appClient.parseAndProcessCommand(inputline);
                refreshTasks();
                message->setText("Done. Enter next command:");
            }
            catch (std::exception e) {
                QString text = QString(e.what());
                message->setText(text);
                refreshTasks();
            }
        }
        else {
            message->setText("NOPE");
            refreshTasks();
        }
    }

    void DoLahUI::goToHome() {
        tabOrganizer->setCurrentIndex(0);
    }

    void DoLahUI::goToDone() {
        tabOrganizer->setCurrentIndex(1);
    }

    void DoLahUI::changeTheme() {
        if (themecounter == 0) {
            QFile stylesheet("night_stylesheet.qss");
            if (stylesheet.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                setStyleSheet(stylesheet.readAll());
                stylesheet.close();
                themecounter = 1;
            }
        }
        else {
            QFile stylesheet("stylesheet.qss");
            if (stylesheet.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                setStyleSheet(stylesheet.readAll());
                stylesheet.close();
                themecounter = 0;
            }
        }
    }

    void DoLahUI::menuExit() {
        exit(0);
    }

}
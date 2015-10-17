#include "DoLahUI.h"

namespace DoLah {
    DoLahUI::DoLahUI(QWidget *parent)
        : QMainWindow(parent)
    {
        this->setupUI();
    }

    DoLahUI::~DoLahUI()
    {

    }

    // MAIN WINDOW

    void DoLahUI::setupUI() {
        if (this->objectName().isEmpty()) {
            this->setObjectName(QStringLiteral("DoLahUIWindow"));
        }
        this->resize(350, 570);
        this->setFixedSize(this->size());
        this->setStyleSheet("background-color: #2A934B;");
        this->setWindowFlags(Qt::CustomizeWindowHint);
        this->setWindowFlags(Qt::FramelessWindowHint);
        centralWidget = new QWidget(this);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        initMenu();
        initDisplayArea();
        initInputArea();

        this->setCentralWidget(centralWidget);

        this->retranslateUI();

        QMetaObject::connectSlotsByName(this);
    }

    void DoLahUI::retranslateUI() {
        this->setWindowTitle(QApplication::translate("window", "DoLah", 0));
        taskBox->setText(QApplication::translate("window", "<font size=4><b>1. polish GUI</b></font><br><font size=3><font color=#20B2AA>today</font></font>", 0));
    }

    // MENU

    void DoLahUI::initMenu() {
        menu = new QHBoxLayout(centralWidget);
        menu->setGeometry(QRect(0, 0, 350, 70));
    }

    // DISPLAY AREA

    void DoLahUI::initDisplayArea() {
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("Scrollable Area"));
        scrollArea->setGeometry(QRect(5, 70, 340, 450));
        scrollArea->setFrameStyle(QFrame::NoFrame);
        scrollArea->setStyleSheet("background-color: #B4EEB4;");

        scrollArea->setWidgetResizable(true);

        taskBox = new QTextBrowser();
        taskBox->setObjectName(QStringLiteral("Task List"));
        taskBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        taskBox->setFixedHeight(40);
        taskBox->setStyleSheet("background-color: white;");
        taskBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        tasksContainer = new QWidget(scrollArea);
        tasksContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        tasksLayout = new QVBoxLayout(tasksContainer);
        tasksLayout->setAlignment(Qt::AlignTop);
        tasksLayout->addWidget(taskBox);
        tasksLayout->setSpacing(3);
        tasksLayout->setMargin(0);
        loadTasks();

        scrollArea->setWidget(tasksContainer);
    }

    void DoLahUI::loadTasks() {
        std::vector<AbstractTask*> taskList = (appClient.getCalendar()).getTaskList();
        for (auto it = taskList.begin(); it != taskList.end(); it++) {
            createTaskBox(*it);
        }
    }

    void DoLahUI::createTaskBox(AbstractTask *task) {
        std::string name = task->getName();
        int id = task->getId();
        // dynamic casting??
        QString tasktitle = "<font size=4><b>" + QString::number(id) + ". " + QString::fromStdString(name);
        QTextBrowser *tempTaskBox = new UITaskBox();
        tempTaskBox->setObjectName(QStringLiteral("Task"));
        tempTaskBox->setText(tasktitle);
        tasksLayout->addWidget(tempTaskBox);
    }

    // INPUT AREA

    void DoLahUI::initInputArea() {
        message = new QLabel(centralWidget);
        message->setText("Enter a command:");
        message->setGeometry(QRect(7, 520, 338, 20));

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("User Input Area"));
        lineEdit->setGeometry(QRect(5, 540, 340, 25));
        lineEdit->setStyleSheet("background-color: white;");
        
        // handles events when enter key is pressed
        QObject::connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(handleUserInput()));
        //QObject::connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(testUserInput()));
        QObject::connect(lineEdit, SIGNAL(returnPressed()), lineEdit, SLOT(clear()));
    }

    void DoLahUI::handleUserInput() {
        QString input = lineEdit->text();
        std::string inputline = input.toStdString();
        this->appClient.parseAndProcessCommand(inputline);
        QTextBrowser *tempTaskBox = new QTextBrowser();
        tempTaskBox->setObjectName(QStringLiteral("Task List"));
        tempTaskBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        tempTaskBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tempTaskBox->setText(input);
        tasksLayout->insertWidget(0, tempTaskBox);
    }

    void DoLahUI::testUserInput() {
        QString input = lineEdit->text();
        QTextBrowser *tempTaskBox = new QTextBrowser();
        tempTaskBox->setObjectName(QStringLiteral("Task List"));
        tempTaskBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        tempTaskBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tempTaskBox->setText(input);
        tasksLayout->insertWidget(0, tempTaskBox);
    }

}
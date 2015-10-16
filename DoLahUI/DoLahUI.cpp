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
        this->resize(350, 500);
        this->setFixedSize(this->size());
        this->setStyleSheet("background-color: #B4EEB4;");
        centralWidget = new QWidget(this);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));

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

    // DISPLAY AREA

    void DoLahUI::initDisplayArea() {
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("Scrollable Area"));
        scrollArea->setGeometry(QRect(0, 0, 350, 450));

        scrollArea->setWidgetResizable(true);

        taskBox = new QTextBrowser();
        taskBox->setObjectName(QStringLiteral("Task List"));
        taskBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        taskBox->setFixedHeight(40);
        taskBox->setStyleSheet("background-color: white;");
        taskBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        taskBox1 = new QTextBrowser();
        taskBox1->setObjectName(QStringLiteral("Task List"));
        taskBox1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        taskBox1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        taskBox2 = new QTextBrowser();
        taskBox2->setObjectName(QStringLiteral("Task List"));
        taskBox2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        taskBox2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        taskBox3 = new QTextBrowser();
        taskBox3->setObjectName(QStringLiteral("Task List"));
        taskBox3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        taskBox3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        taskBox4 = new QTextBrowser();
        taskBox4->setObjectName(QStringLiteral("Task List"));
        taskBox4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        taskBox4->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        tasksContainer = new QWidget(scrollArea);
        tasksContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        tasksLayout = new QVBoxLayout(tasksContainer);
        tasksLayout->setAlignment(Qt::AlignTop);
        tasksLayout->addWidget(taskBox);
        //tasksLayout->addWidget(taskBox1);
        //tasksLayout->addWidget(taskBox2);
        //tasksLayout->addWidget(taskBox3);
        //tasksLayout->addWidget(taskBox4);
        tasksLayout->setSpacing(5);
        tasksLayout->setMargin(5);
        //loadTasks();

        scrollArea->setWidget(tasksContainer);
    }

    void DoLahUI::loadTasks() {
        std::vector<AbstractTask*> taskList = (appClient.getCalendar()).getTaskList();
        for (auto it = taskList.begin(); it != taskList.end(); it++) {
            createTaskBox(*it);
        }
    }

    void DoLahUI::createTaskBox(AbstractTask *task) {
        const char* description = (task->getDescription()).c_str();
        int id = task->getId();
        QTextBrowser *tempTaskBox = new QTextBrowser();
        tempTaskBox->setObjectName(QStringLiteral("Task List"));
        tempTaskBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        tempTaskBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tempTaskBox->setText(QString::number(id) + ". ");
        tempTaskBox->append(QApplication::translate("window", description, 0));
        tasksLayout->addWidget(tempTaskBox);
    }

    // INPUT AREA

    void DoLahUI::initInputArea() {
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("User Input Area"));
        lineEdit->setGeometry(QRect(5, 465, 340, 25));
        lineEdit->setStyleSheet("background-color: white;");
        
        // handles events when enter key is pressed
        //QObject::connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(handleUserInput()));
        QObject::connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(testUserInput()));
        QObject::connect(lineEdit, SIGNAL(returnPressed()), lineEdit, SLOT(clear()));
    }

    void DoLahUI::handleUserInput() {
        this->appClient.parseAndProcessCommand(lineEdit->text().toStdString());
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
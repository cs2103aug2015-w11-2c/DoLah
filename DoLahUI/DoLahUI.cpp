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

    void DoLahUI::setupUI() {
        if (this->objectName().isEmpty()) {
            this->setObjectName(QStringLiteral("DoLahUIWindow"));
        }
        this->resize(350, 500);
        this->setFixedSize(this->size());
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
        taskBox->setText(QApplication::translate("window", "Label???ahsdkfhlakshdflkhjalskdjhfkjahslkdhjflkahjsdlkfjhlasdfiuiudfhiahsoidfhiuahifuhaisufhiuhsdfiuhawieufhqieufhiquwhid", 0));
    }

    void DoLahUI::initDisplayArea() {
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("Scrollable Area"));
        scrollArea->setGeometry(QRect(0, 0, 350, 450));

        scrollArea->setWidgetResizable(true);

        taskBox = new QTextBrowser();
        taskBox->setObjectName(QStringLiteral("Task List"));
        taskBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
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

        taskBox5 = new QTextBrowser();
        taskBox5->setObjectName(QStringLiteral("Task List")); 
        taskBox5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        taskBox5->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        tasksContainer = new QWidget(scrollArea);
        tasksContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        tasksLayout = new QVBoxLayout(tasksContainer);
        tasksLayout->addWidget(taskBox);
        tasksLayout->addWidget(taskBox1);
        tasksLayout->addWidget(taskBox2);
        tasksLayout->addWidget(taskBox3);
        tasksLayout->addWidget(taskBox4);
        tasksLayout->addWidget(taskBox5);
        tasksLayout->setSpacing(10);
        tasksLayout->setMargin(0);

        scrollArea->setWidget(tasksContainer);
    }

    void DoLahUI::initInputArea() {
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("User Input Area"));
        lineEdit->setGeometry(QRect(5, 460, 340, 25));

        QObject::connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(appClient.parseAndProcessCommand(lineEdit->text())));
        QObject::connect(lineEdit, SIGNAL(returnPressed()), lineEdit, SLOT(clear()));
    }

    void DoLahUI::createTaskBox(AbstractTask *task) {
        const char* description = (task->getDescription()).c_str();
        QTextBrowser *tempTaskBox = new QTextBrowser();
        tempTaskBox->setObjectName(QStringLiteral("Task List"));
        tempTaskBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        tempTaskBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tempTaskBox->setText(QApplication::translate("window", description, 0));
        tasksLayout->addWidget(tempTaskBox);
    }

}
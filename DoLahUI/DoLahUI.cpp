#include "DoLahUI.h"

namespace DoLah {
    DoLahUI::DoLahUI(QWidget *parent)
        : QMainWindow(parent)
    {
        this->setupUI();
        //this->eventHandler();
    }

    DoLahUI::~DoLahUI()
    {

    }

    void DoLahUI::setupUI() {
        if (this->objectName().isEmpty()) {
            this->setObjectName(QStringLiteral("DoLahUIWindow"));
        }
        this->resize(350, 500);
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
        taskBox->setText(QApplication::translate("window", "Label???ahsdkfhlakshdflkhjalskdjhfkjahslkdhjflkahjsdlkfjhlasdfiuiudfhiahsoidfhiuahifuhaisufhiuhsdfiuhawieufhqieufhiquwhid\n\nTEST", 0));
    }

    void DoLahUI::initDisplayArea() {
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("Scrollable Area"));
        scrollArea->setGeometry(QRect(0, 0, 350, 450));

        scrollArea->setWidgetResizable(true);

        taskBox = new QTextBrowser();
        taskBox->setObjectName(QStringLiteral("Task List"));
        taskBox->setGeometry(QRect(0, 0, 350, 200));
        taskBox->setMaximumHeight(500);
        taskBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        taskBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        taskBox1 = new QTextBrowser();
        taskBox1->setObjectName(QStringLiteral("Task List"));
        taskBox1->setGeometry(QRect(0, 0, 350, 90));
        taskBox1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        taskBox2 = new QTextBrowser();
        taskBox2->setObjectName(QStringLiteral("Task List"));
        taskBox2->setGeometry(QRect(0, 0, 350, 90));
        taskBox2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        taskBox3 = new QTextBrowser();
        taskBox3->setObjectName(QStringLiteral("Task List"));
        taskBox3->setGeometry(QRect(0, 0, 350, 90));
        taskBox3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        taskBox4 = new QTextBrowser();
        taskBox4->setObjectName(QStringLiteral("Task List"));
        taskBox4->setGeometry(QRect(0, 0, 350, 90));
        taskBox4->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        taskBox5 = new QTextBrowser();
        taskBox5->setObjectName(QStringLiteral("Task List"));
        taskBox5->setGeometry(QRect(0, 0, 350, 90));
        taskBox5->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        taskBox6 = new QTextBrowser();
        taskBox6->setObjectName(QStringLiteral("Task List"));
        taskBox6->setGeometry(QRect(0, 0, 350, 90));
        taskBox6->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        tasksContainer = new QWidget();
        tasksContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

        tasksLayout = new QVBoxLayout(tasksContainer);
        tasksLayout->addWidget(taskBox);
        tasksLayout->addWidget(taskBox1);
        tasksLayout->addWidget(taskBox2);
        tasksLayout->addWidget(taskBox3);
        tasksLayout->addWidget(taskBox4);
        tasksLayout->addWidget(taskBox5);
        tasksLayout->addWidget(taskBox6);
        tasksLayout->setSpacing(10);
        tasksLayout->setMargin(0);

        scrollArea->setWidget(tasksContainer);
    }

    void DoLahUI::initInputArea() {
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("User Input Area"));
        lineEdit->setGeometry(QRect(5, 460, 340, 25));
    }

    //void DoLahUI::eventHandler() {
    //  Qt::Key_Enter
    //}
}
#include "DoLahUI.h"

DoLahUI::DoLahUI(QWidget *parent)
    : QMainWindow(parent)
{
    this->setupUI();
}

DoLahUI::~DoLahUI()
{
    
}

void DoLahUI::setupUI() {
    if(this->objectName().isEmpty()) {
        this->setObjectName(QStringLiteral("DoLahUIWindow"));
    }
    this->resize(531, 475);
    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));

    initDisplayArea();

    lineEdit = new QLineEdit(centralWidget);
    lineEdit->setObjectName(QStringLiteral("lineEdit"));
    lineEdit->setGeometry(QRect(0, 400, 491, 31));

    pushButton = new QPushButton(centralWidget);
    pushButton->setObjectName(QStringLiteral("pushButton"));
    pushButton->setGeometry(QRect(500, 400, 31, 31));

    this->setCentralWidget(centralWidget);

    this->retranslateUI();

    QMetaObject::connectSlotsByName(this);
}

void DoLahUI::retranslateUI() {
    this->setWindowTitle(QApplication::translate("window", "DoLah", 0));
    tasksLabel->setText(QApplication::translate("window", "Label???ahsdkfhlakshdflkhjalskdjhfkjahslkdhjflkahjsdlkfjhlasdfiuiudfhiahsoidfhiuahifuhaisufhiuhsdfiuhawieufhqieufhiquwhidfuhiquwhdfihs\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nTEST", 0));
    pushButton->setText(QApplication::translate("window", "GO", 0));
}

void DoLahUI::initDisplayArea() {
    scrollArea = new QScrollArea(centralWidget);
    scrollArea->setObjectName(QStringLiteral("scrollArea"));
    scrollArea->setGeometry(QRect(0, 0, 531, 391));
    scrollArea->setWidgetResizable(true);

    tasksLabel = new QLabel;
    tasksLabel->setObjectName(QStringLiteral("Task List"));
    tasksLabel->setGeometry(QRect(0, 0, 521, 391));
    tasksLabel->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);
    tasksLabel->setWordWrap(true);
    tasksLabel->setMargin(10);
    scrollArea->setWidget(tasksLabel);
}
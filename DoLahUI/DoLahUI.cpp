#include "DoLahUI.h"

DoLahUI::DoLahUI(QWidget *parent)
    : QMainWindow(parent)
{
    this->setupUi();
}

DoLahUI::~DoLahUI()
{
    
}

void DoLahUI::setupUi()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("DoLahUIWindow"));
    this->resize(531, 475);
    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    scrollArea = new QScrollArea(centralWidget);
    scrollArea->setObjectName(QStringLiteral("scrollArea"));
    scrollArea->setGeometry(QRect(0, 0, 531, 391));
    scrollArea->setWidgetResizable(true);
    scrollAreaWidgetContents = new QWidget();
    scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
    scrollAreaWidgetContents->setGeometry(QRect(0, 0, 529, 389));
    label = new QLabel(scrollAreaWidgetContents);
    label->setObjectName(QStringLiteral("label"));
    label->setGeometry(QRect(0, 0, 521, 391));
    label->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);
    label->setMargin(10);
    scrollArea->setWidget(scrollAreaWidgetContents);
    lineEdit = new QLineEdit(centralWidget);
    lineEdit->setObjectName(QStringLiteral("lineEdit"));
    lineEdit->setGeometry(QRect(0, 400, 491, 31));
    pushButton = new QPushButton(centralWidget);
    pushButton->setObjectName(QStringLiteral("pushButton"));
    pushButton->setGeometry(QRect(500, 400, 31, 31));
    this->setCentralWidget(centralWidget);

    this->retranslateUi();

    QMetaObject::connectSlotsByName(this);
} // setupUi

void DoLahUI::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("window", "DoLah", 0));
    label->setText(QApplication::translate("window", "Label???", 0));
    pushButton->setText(QApplication::translate("window", "GO", 0));
} // retranslateUi
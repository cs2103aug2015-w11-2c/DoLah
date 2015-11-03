#include "SettingsWindow.h"


namespace DoLah {
    SettingsWindow::SettingsWindow(QMainWindow * parent) {
        this->mainWin = parent;
        this->setParent(parent);
        this->resize(300, 250);
        this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::Dialog);
        themeOptions();

        exitButton = new MenuLabel(this);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        QPixmap exitIcon("images/dialog_exit.png");
        exitButton->setPixmap(exitIcon);
        exitButton->setGeometry(QRect(270, 0, 20, 20));
        QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(reject()));

        buttonBox = new QDialogButtonBox(this);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(65, 170, 170, 23));
        buttonBox->setCenterButtons(true);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
        connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    }

    SettingsWindow::~SettingsWindow()
    {
    }

    void SettingsWindow::themeOptions() {
        themeSelection = new QComboBox(this);
        themeSelection->addItem("Default");
        themeSelection->addItem("Windows 10");
        themeSelection->setGeometry(QRect(50, 100, 200, 20));
        connect(themeSelection, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTheme(int)));
    }

    void SettingsWindow::changeTheme(int index) {
        if (index == 0) {
            readAndSetStyleSheet("stylesheets/stylesheet.qss");
            themeSelection->setCurrentIndex(0);
        }
        else if (index == 1) {
            readAndSetStyleSheet("stylesheets/night_stylesheet.qss");
            themeSelection->setCurrentIndex(1);
        }
    }

    void SettingsWindow::readAndSetStyleSheet(const char *qss) {
        QFile stylesheet(qss);
        if (stylesheet.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            mainWin->setStyleSheet(stylesheet.readAll());
            stylesheet.close();
        }
    }
}
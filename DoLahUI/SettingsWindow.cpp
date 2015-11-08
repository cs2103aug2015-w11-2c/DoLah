#include "SettingsWindow.h"


namespace DoLah {
    SettingsWindow::SettingsWindow(QMainWindow * parent) {
        this->mainWin = parent;
        this->setParent(parent);
        this->resize(300, 270);
        this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::Dialog);
        storageSettings();
        themeOptions();

        exitButton = new MenuLabel(this);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        QPixmap exitIcon("images/dialog_exit.png");
        exitButton->setPixmap(exitIcon);
        exitButton->setGeometry(QRect(270, 0, 20, 20));
        QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(reject()));

        buttonBox = new QDialogButtonBox(this);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(0, 220, 300, 23));
        buttonBox->setCenterButtons(true);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        connect(buttonBox, SIGNAL(accepted()), this, SLOT(applyChanges()));
        connect(buttonBox, SIGNAL(rejected()), this, SLOT(cancelChanges()));
    }

    SettingsWindow::~SettingsWindow()
    {
    }

    void SettingsWindow::storageSettings() {
        fileBrowser = new QFileDialog(this);
        fileBrowser->setFileMode(QFileDialog::Directory);
        storageLocationBox = new QLineEdit(this);
        storageLocationBox->setReadOnly(true);
        storageLocationBox->setGeometry(QRect(20, 100, 200, 20));
        Configuration config = ConfigurationManager::loadConfig();
        originalLocation = QString::fromUtf8(config.storagefile.c_str());
        if (originalLocation == "calendar.yaml") {
            originalLocation = QDir::currentPath();
        }
        else {
            originalLocation.remove("/calendar.yaml");
        }
        storageLocationBox->setText(originalLocation);
        browseButton = new QPushButton(this);
        browseButton->setText("Browse");
        browseButton->setGeometry(QRect(230, 98, 50, 23));
        connect(browseButton, SIGNAL(clicked()), this, SLOT(browseLocation()));
    }

    void SettingsWindow::themeOptions() {
        themeSelection = new QComboBox(this);
        themeSelection->addItem("Default");
        themeSelection->addItem("Night");
        themeSelection->addItem("Ordinaire");
        themeSelection->setGeometry(QRect(50, 170, 200, 20));
        originalTheme = themeSelection->currentIndex();
        connect(themeSelection, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTheme(int)));
    }

    void SettingsWindow::browseLocation() {
        selectedLocation = fileBrowser->getExistingDirectory(this, tr("Select Task Data Storage Location"));
        if (selectedLocation.length() != 0) {
            storageLocationBox->setText(selectedLocation);
        }
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
        else if (index == 2) {
            readAndSetStyleSheet("stylesheets/ordinaire_stylesheet.qss");
            themeSelection->setCurrentIndex(2);
        }
    }

    void SettingsWindow::applyChanges() {
        originalTheme = themeSelection->currentIndex();
        QString formattedUrl;
        if (storageLocationBox->text() == originalLocation) {
        }
        else {
            originalLocation = storageLocationBox->text();
            formattedUrl = originalLocation + "/calendar.yaml";
            emit applyStorageSettings(formattedUrl);
        }
        this->accept();
    }

    void SettingsWindow::cancelChanges() {
        changeTheme(originalTheme);
        storageLocationBox->setText(originalLocation);
        this->reject();
    }

    void SettingsWindow::readAndSetStyleSheet(const char *qss) {
        QFile stylesheet(qss);
        if (stylesheet.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            mainWin->setStyleSheet(stylesheet.readAll());
            stylesheet.close();
        }
    }

    void SettingsWindow::keyPressEvent(QKeyEvent *event) {
        if (event->key() == Qt::Key_Escape) {
            this->cancelChanges();
        }
        else {
            QDialog::keyPressEvent(event);
        }
    }
}
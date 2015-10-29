#pragma once

#include <QtWidgets/QDialog>

namespace DoLah {
    class SettingsWindow :
        public QDialog
    {
        Q_OBJECT

    public:
        SettingsWindow();
        ~SettingsWindow();
    };
}

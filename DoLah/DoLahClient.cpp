#include "DoLahClient.h"
#include "Commands/Command.h"
#include "Parser/CommandParser.h"
#include "CommandInvoker.h"
#include "Storage/CalendarStorage.h"

namespace DoLah {

    DoLahClient::DoLahClient() {
        this->restart();
    }

    DoLahClient::~DoLahClient() {

    }

    void DoLahClient::parseAndProcessCommand(std::string userinput) {
        DoLah::AbstractCommand *command = CommandParser::parse(userinput);
        command->setCalendar(&calendar);
        this->commandInvoker.process(command);
        DoLah::CalendarStorage::save(calendar, this->config.storagefile);
    }

    Calendar DoLahClient::getCalendar() const {
        return this->calendar;
    }

    void DoLahClient::setStorageLocation(std::string location) {
        this->config.storagefile = location;
        ConfigurationManager::saveConfig(this->config);
        this->restart();
    }

    void DoLahClient::setTheme(int themeno) {
        this->config.theme = themeno;
        ConfigurationManager::saveConfig(this->config);
    }

    void DoLahClient::restart() {
        this->config = ConfigurationManager::loadConfig();
        this->calendar = DoLah::CalendarStorage::load(this->config.storagefile);
        this->commandInvoker = CommandInvoker();
        CommandHistory* cmdHistory = (this->calendar.getCmdHistory());
        this->commandInvoker.setCmdHistory(cmdHistory);
    }
}

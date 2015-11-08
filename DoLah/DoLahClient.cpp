#include "DoLahClient.h"
#include "Commands/Command.h"
#include "Parser/CommandParser.h"
#include "CommandInvoker.h"
#include "Storage/CalendarStorage.h"

namespace DoLah {

    DoLahClient::DoLahClient() {
        this->config = ConfigurationManager::loadConfig();
        this->calendar = DoLah::CalendarStorage::load(this->config.storagefile);
        this->commandInvoker = CommandInvoker();
        CommandHistory* cmdHistory = (this->calendar.getCmdHistory());
        this->commandInvoker.setCmdHistory(cmdHistory);
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

    std::string DoLahClient::getStorageLocation() {
        return this->config.storagefile;
    }

    void DoLahClient::setStorageLocation(std::string location) {
        this->config.storagefile = location;
        ConfigurationManager::saveConfig(this->config);
    }
}

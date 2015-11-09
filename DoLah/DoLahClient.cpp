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

    Calendar DoLahClient::getCalendar() const {
        return this->calendar;
    }

    void DoLahClient::setStorageLocation(std::string location) {
        this->config.storagefile = location;
        ConfigurationManager::saveConfig(this->config);
        this->restart();
    }

    void DoLahClient::parseAndProcessCommand(std::string userInput) {
        DoLah::AbstractCommand *command = CommandParser::parse(userInput);
        command->setCalendar(&calendar);
        this->commandInvoker.process(command);
        DoLah::CalendarStorage::save(calendar, this->config.storagefile);
    }

    void DoLahClient::restart() {
        this->config = ConfigurationManager::loadConfig();
        this->calendar = DoLah::CalendarStorage::load(this->config.storagefile);
        this->commandInvoker = CommandInvoker();
        CommandHistory* cmdHistory = (this->calendar.getCmdHistory());
        this->commandInvoker.setCmdHistory(cmdHistory);
    }
}

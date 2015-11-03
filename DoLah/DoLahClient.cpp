#include "DoLahClient.h"
#include "Commands/Command.h"
#include "Parser/CommandParser.h"
#include "CommandInvoker.h"
#include "Storage/CalendarStorage.h"

namespace DoLah {
    static const std::string DEFAULT_CALENDAR_FILENAME = "calendar.yaml";

    DoLahClient::DoLahClient() {
        this->calendar = DoLah::CalendarStorage::load(DEFAULT_CALENDAR_FILENAME);
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
        DoLah::CalendarStorage::save(calendar, DEFAULT_CALENDAR_FILENAME);
    }

    Calendar DoLahClient::getCalendar() const {
        return this->calendar;
    }
}

#include "DoLahClient.h"
#include "Commands/Command.h"
#include "Parser/CommandParser.h"
#include "CommandInvoker.h"

namespace DoLah {

    DoLahClient::DoLahClient() {

    }


    DoLahClient::~DoLahClient() {

    }

    void DoLahClient::parseAndProcessCommand(std::string userinput) {
        DoLah::ITaskCommand *command = CommandParser::parse(userinput);
        command->setCalendar(&calendar);
        DoLah::CommandInvoker::process(command);
    }

    Calendar DoLahClient::getCalendar() const {
        return this->calendar;
    }

    void DoLahClient::save() {
        // save to storageFile
    }

    void DoLahClient::load() {
        // load settingsFile and storageFile
    }
}
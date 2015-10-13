#include "DoLahClient.h"
#include "Commands/Command.h"
#include "CommandParser.h"
#include "CommandInvoker.h"

namespace DoLah {

    DoLahClient::DoLahClient() {

    }


    DoLahClient::~DoLahClient() {

    }

    void DoLahClient::parseAndProcessCommand(std::string userinput) {
        DoLah::ITaskCommand *command = CommandParser::parse(userinput);
        DoLah::CommandInvoker::process(command);
    }

    void DoLahClient::save() {
        // save to storageFile
    }

    void DoLahClient::load() {
        // load settingsFile and storageFile
    }
}
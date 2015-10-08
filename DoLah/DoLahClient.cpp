#include "DoLahClient.h"

namespace DoLah {

    DoLahClient::DoLahClient() {

    }


    DoLahClient::~DoLahClient() {

    }

    void DoLahClient::parseAndProcessCommand(std::string userinput) {
        //DoLah::ITaskCommand *command = CommandParser::parse(userinput);
        //injectCalendar(command); ???
        //processor.process(command);
    }

    void DoLahClient::save() {
        // save to storageFile
    }

    void DoLahClient::load() {
        // load settingsFile and storageFile
    }
}
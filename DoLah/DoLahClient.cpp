#include "DoLahClient.h"

namespace DoLah {
    DoLahClient::DoLahClient() { }


    DoLahClient::~DoLahClient() {  }

    void DoLahClient::parseAndProcessCommand(std::string userinput) {
        //DoLah::ITaskCommand command = DoLah::CommandParser::parse(userinput);
        //DoLah::CommandInvoker::process(command);
    }

    void DoLahClient::save() {
        // save to storageFile
    }

    void DoLahClient::load() {
        // load settingsFile and storageFile
    }
}

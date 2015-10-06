#include "DoLahClient.h"

DoLahClient::DoLahClient() {
    calendar = new Calendar();
    processor = new CalendarProcessor();
    parser = new TaskCommandParser();
}


DoLahClient::~DoLahClient() {
    
}

void DoLahClient::parseAndProcessCommand(std::string userinput) {
    iTaskCommand command = parser.parse(userinput);
    processor.process(command);
}

void DoLahClient::save() {
    // save to storageFile
}

void DoLahClient::load() {
    // load settingsFile and storageFile
}

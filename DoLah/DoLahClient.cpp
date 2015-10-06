#include "DoLahClient.h"

<<<<<<< HEAD


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
=======
namespace DoLah {

	DoLahClient::DoLahClient() {

	}

	void DoLahClient::parseAndProcessCommand(std::string line) {
		//TODO
	}

>>>>>>> 161c5e565b91c9582f05fe3195de50a1664b0d34
}
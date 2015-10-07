#include "DoLahClient.h"

namespace DoLah {

	DoLahClient::DoLahClient() {

	}


	void DoLahClient::parseAndProcessCommand(std::string line) {
        DoLah::ITaskCommand* command = DoLah::CommandParser::parse(line);
        command->execute();
	}


    void DoLahClient::save() {
    }


    void DoLahClient::load() {
    }
}
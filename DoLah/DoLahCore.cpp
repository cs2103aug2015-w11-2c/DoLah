#include "DoLahCore.h"

namespace DoLah {

	DoLahCore::DoLahCore(std::string settings, std::string storage){
		settingsFile = settings;
		storageFile = storage;
	};

	std::vector<std::string> DoLahCore::DoLah(std::string line){
		//tokenList = tokenize(line)
		std::vector<ITokenObject> tokenList;

		DoLah::ITaskCommand* command = DoLahCore::parseTaskCommand(tokenList);
		command->execute();
	}

	DoLah::ITaskCommand* parseTaskCommand(std::vector<ITokenObject> tokenVector) {
		//TODO: if/else block to choose correct command class, then instantiate the class with the vector
	}

	void DoLahCore::save() {

	}

	void DoLahCore::load() {

	}
}
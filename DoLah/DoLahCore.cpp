#include "DoLahCore.h"

namespace DoLah {

	DoLahCore::DoLahCore(std::string settings, std::string storage){
		settingsFile = settings;
		storageFile = storage;
	};

	//std::vector<std::string> DoLahCore::DoLah(std::string line){
	//	//tokenList = tokenize(line)
	//	std::vector<ITokenObject> tokenList;

	//	DoLah::ITaskCommand* command = DoLahCore::parseTaskCommand(tokenList);
	//	command->execute();
	//}

	//DoLah::ITaskCommand* parseTaskCommand(std::vector<ITokenObject> tokenVector) {
	//	//TODO: if/else block to choose correct command class, then instantiate the class with the vector
	//}

	//void DoLahCore::save() {
	//	std::fstream storage(DoLahCore::storageFile, std::fstream::in);

	//	//TODO: Function calls to convert taskList and then write to file
	//	//TODO: Settings file
	//	
	//	storage.close();
	//}

	//void DoLahCore::load() {
	//	std::fstream storage(DoLahCore::storageFile, std::fstream::out);

	//	//TODO: Function calls to convert lines from file then add to taskList
	//	//TODO: Settings file
	//	
	//	storage.close();
	//}
}
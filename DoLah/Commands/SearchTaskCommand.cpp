#include "Command.h"

namespace DoLah {
	//public
	SearchTaskCommand::SearchTaskCommand() {

	}

    SearchTaskCommand::SearchTaskCommand(std::string searchString) {
        query = searchString;
    }

	SearchTaskCommand::SearchTaskCommand(std::string searchString, std::vector<AbstractTask*> * resVector) {
		query = searchString;
        resultVector = &resVector;
	}

	SearchTaskCommand::~SearchTaskCommand() {

	}

	void SearchTaskCommand::execute() {
		this->calendar->search(query);
	}

	//private
}
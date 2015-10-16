#include "Command.h"

namespace DoLah {
	//public
	SearchTaskCommand::SearchTaskCommand() {

	}

	SearchTaskCommand::SearchTaskCommand(std::string searchString) {
		query = searchString;
	}

	SearchTaskCommand::~SearchTaskCommand() {

	}

	void SearchTaskCommand::execute() {
		this->calendar->search(query);
	}

	//private
}
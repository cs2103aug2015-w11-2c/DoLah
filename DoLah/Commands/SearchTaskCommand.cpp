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
		calendar.search(query);
	}

	//private
}
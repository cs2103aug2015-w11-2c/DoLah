#include "Command.h"

namespace DoLah {
	//public
	SearchTaskCommand::SearchTaskCommand() {

	}

	SearchTaskCommand::~SearchTaskCommand() {

	}

	std::string SearchTaskCommand::getQuery() {
		return query;
	}

	void SearchTaskCommand::setQuery(std::string newQuery) {
		query = newQuery;
	}

	void SearchTaskCommand::execute() {
		//TODO
	}

	//private
}
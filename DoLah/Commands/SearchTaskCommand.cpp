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

    std::vector<AbstractTask*> SearchTaskCommand::getResultVector() {
        return **resultVector;
    }

    void SearchTaskCommand::setResultVector(std::vector<AbstractTask*> * resVector) {
        resultVector = &resVector;
    }

	void SearchTaskCommand::execute() {
		**resultVector = (this->calendar->search(query));
	}

    void SearchTaskCommand::revert() {
        CalendarInverter::invertSearch(resultVector, query, calendar);
    }

	//private
}
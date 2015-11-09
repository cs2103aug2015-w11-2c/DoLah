//@@collate A0111275R
#include "Command.h"

namespace DoLah {
    //public

    SearchTaskCommand::SearchTaskCommand(std::string searchString) {
        query = searchString;
    }

    SearchTaskCommand::~SearchTaskCommand() {

    }

    void SearchTaskCommand::execute() {
        this->calendar->search(query);
    }

    void SearchTaskCommand::revert() {
        CalendarInverter::invertSearch(query, calendar);
    }

    //private
}
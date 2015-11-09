#include "Command.h"

namespace DoLah {
    //public
    SearchDateTaskCommand::SearchDateTaskCommand(std::tm from, std::tm to) {
        this->from = from;
        this->to = to;
    }

    SearchDateTaskCommand::~SearchDateTaskCommand() {

    }

    void SearchDateTaskCommand::execute() {
        this->calendar->searchDate(from, to);
    }

    void SearchDateTaskCommand::revert() {
    }

    //private
}
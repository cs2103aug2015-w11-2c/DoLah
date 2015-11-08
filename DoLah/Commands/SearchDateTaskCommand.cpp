#include "Command.h"

namespace DoLah {
    SearchDateTaskCommand::SearchDateTaskCommand() {
    }

    SearchDateTaskCommand::SearchDateTaskCommand(std::tm from, std::tm to) {
        this->from = from;
        this->to = to;
    }

    SearchDateTaskCommand::SearchDateTaskCommand(std::tm from, std::tm to, std::vector<AbstractTask*> * resVector) {
        this->from = from;
        this->to = to;
        resultVector = &resVector;
    }

    SearchDateTaskCommand::~SearchDateTaskCommand() {

    }

    void SearchDateTaskCommand::execute() {
        this->calendar->searchDate(from, to);
    }

    void SearchDateTaskCommand::revert() {
        CalendarInverter::invertSearchDate(resultVector, from, to, calendar);
    }
}
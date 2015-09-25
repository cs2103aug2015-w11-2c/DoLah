#include "ITokenObject.h"

void DateTimeToken::setDate(std::chrono::system_clock::time_point input) {
    this->data = input;
}
std::chrono::system_clock::time_point DateTimeToken::getData() {
    return this->data;
}

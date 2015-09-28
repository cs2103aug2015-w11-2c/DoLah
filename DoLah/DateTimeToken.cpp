#include "ITokenObject.h"

void DateTimeToken::setData(std::chrono::system_clock::time_point input) {
    this->data = { input };
}
void DateTimeToken::setData(std::vector<std::chrono::system_clock::time_point> input) {
    this->data = input;
}
std::vector<std::chrono::system_clock::time_point> DateTimeToken::getDateTimeVector() {
    return this->data;
}

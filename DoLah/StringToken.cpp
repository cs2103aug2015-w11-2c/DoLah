#include "ITokenObject.h"

void StringToken::setData(std::string input) {
    this->data = { input };
}
void StringToken::setData(std::vector<std::string> input) {
    this->data = input;
}
std::vector<std::string> StringToken::getStringVector() {
    return this->data;
}

#include "ITokenObject.h"

void StringToken::setData(std::string input) {
    this->data = input;
}
std::string StringToken::getData() {
    return this->data;
}

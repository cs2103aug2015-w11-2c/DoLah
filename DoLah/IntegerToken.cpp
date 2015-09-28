#include "ITokenObject.h"

void IntegerToken::setData(std::vector<int> input) {
    this->data = input;
}
std::vector<int> IntegerToken::getData() {
    return this->data;
}
#include "ITokenObject.h"

void IntegerToken::setData(int input) {
    this->data = { input };
}
void IntegerToken::setData(std::vector<int> input) {
    this->data = input;
}
std::vector<int> IntegerToken::getIntegerVector() {
    return this->data;
}
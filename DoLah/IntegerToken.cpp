#include "ITokenObject.h"

void IntegerToken::setData(int input) {
    this->data = input;
}
int IntegerToken::getData() {
    return this->data;
}
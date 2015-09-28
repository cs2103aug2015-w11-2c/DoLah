#include "ITokenObject.h"



ITokenObject::ITokenObject() {
}


ITokenObject::~ITokenObject() {
}


std::vector<int> ITokenObject::getIntegerVector() {
    return {};
}
std::vector<std::string> ITokenObject::getStringVector() {
    return{};
}
std::vector<std::chrono::system_clock::time_point> ITokenObject::getDateTimeVector() {
    return{};
}
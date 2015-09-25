#pragma once
#include <string>
#include <chrono>

class ITokenObject {
public:
    ITokenObject();
    ~ITokenObject();
};

class DateTimeToken : public ITokenObject {
public:
    std::chrono::system_clock::time_point data;
    void setDate(std::chrono::system_clock::time_point input);
    std::chrono::system_clock::time_point getData();
};

class StringToken : public ITokenObject {
public:
    std::string data;
    void setData(std::string input);
    std::string getData();
};

class IntegerToken : public ITokenObject {
public:
    int data;
    void setData(int input);
    int getData();
};
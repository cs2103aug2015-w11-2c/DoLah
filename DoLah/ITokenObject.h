#pragma once
#include <string>
#include <vector>
#include <chrono>

class ITokenObject {
public:
    ITokenObject();
    ~ITokenObject();
};

class DateTimeToken : public ITokenObject {
public:
    std::vector<std::chrono::system_clock::time_point> data;
    void setDate(std::chrono::system_clock::time_point input);
    void setDate(std::vector<std::chrono::system_clock::time_point> input);
    std::vector<std::chrono::system_clock::time_point> getData();
};

class StringToken : public ITokenObject {
public:
    std::vector<std::string> data;
    void setData(std::string input);
    void setData(std::vector<std::string> input);
    std::vector<std::string> getData();
};

class IntegerToken : public ITokenObject {
public:
    std::vector<int> data;
    void setData(int input);
    void setData(std::vector<int> input);
    std::vector<int> getData();
};
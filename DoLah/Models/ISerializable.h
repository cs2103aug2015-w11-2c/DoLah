#pragma once
#include <string>

class ISerializable {
public:
    virtual ISerializable* serialize(const std::string&) = 0;
    virtual std::string deserialize() = 0;
};
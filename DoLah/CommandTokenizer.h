#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <regex>
#include <iterator>

#include "ParserLibrary.h"

class CommandTokenizer {
public:
    CommandTokenizer();
    ~CommandTokenizer();

    std::string findCommand(std::vector<std::string> lineArr);

    std::string findDescription(std::vector<std::string> lineArr);
    std::vector<std::string> findTags(std::vector<std::string> lineArr);
    std::vector<std::tm> findDate(std::vector<std::string> lineArr);

    // decision tree to classify the input as dateformat or not
    // accepts DD, DD-MM, DD-MM-YYYY, MM-DD, MM-DD-YYYY
    // consider changing into toDateFormat to do everything at once
    std::tm toDateFormat(std::vector<std::string>);
    int getDay(std::string);
    int getMonth(std::string);
    int getYear(std::string);

    bool isDecimal(std::string);

private:
    std::vector<std::string> commandList = { "add", "display", "undo", "delete", "edit", "clear", "search", "sort" };
    std::vector<std::string> timeSubCommandList = { "on" };

    std::string tag = "#";


    std::string relativePattern = "this|next";
    std::string datePattern = "^("
        "monday|tuesday|wednesday|thursday|friday|saturday|sunday"
        "|mon|tue|wed|thu|fri|sat|sun"
        ")$";
    std::string dayPattern = "^("
        "([1-9]|0[1-9]|[1-2][0-9]|[3][0-1])(st|nd|rd|th|$)"
        ")$";
    std::string dayAppendixPattern = "(st|nd|rd|th)$";
    std::vector<std::string> monthPattern = {
        "^(january|jan|01|1)$",
        "^(february|feb|02|2)$",
        "^(march|mar|03|3)$",
        "^(april|apr|04|4)$",
        "^(may|05|5)$",
        "^(june|jun|06|6)$",
        "^(july|jul|07|7)$",
        "^(august|aug|08|8)$",
        "^(september|sep|09|9)$",
        "^(october|oct|10)$",
        "^(november|nov|11)$",
        "^(december|dec|12)$"
    };

    std::vector<std::string> monthFormat = {
        "^(january|jan|1|01)$",
    };



    std::string UNKNOWN_COMMAND_MESSAGE = "command not recognized";
};


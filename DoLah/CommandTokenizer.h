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
    std::vector<std::chrono::system_clock::time_point> findDate(std::vector<std::string> lineArr);

    // decision tree to classify the input as dateformat or not
    // accepts DD, DD-MM, DD-MM-YYYY, MM-DD, MM-DD-YYYY
    // consider changing into toDateFormat to do everything at once
    bool isDateFormat(std::vector<std::string>);
    bool isDate(std::string);
    bool isDay(std::string);
    int getDay(std::string);
    bool isMonth(std::string);
    bool isYear(std::string);
    std::chrono::system_clock::time_point DMYToTimePoint(std::vector<std::string>);

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
    std::string monthPattern = "^("
        // consider finding alterntive for the first line to speed up the process
        "january|february|march|april|may|june|july|august|september|october|november|december"
        "|jan|feb|mar|apr|may|jun|jul|aug|sep|oct|nov|dec"
        "|[1-9]|0[1-9]|1[0-2]"
        ")$";

    std::vector<std::string> monthFormat = {
        "^(january|jan|1|01)$",
    };



    std::string UNKNOWN_COMMAND_MESSAGE = "command not recognized";
};


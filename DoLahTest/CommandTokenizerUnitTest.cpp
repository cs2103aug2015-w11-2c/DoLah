#include "stdafx.h"
#include "CppUnitTest.h"
#include "regex"
#include <iterator>


#include "basic.h"

#include "CommandTokenizer.h"
#include "ParserLibrary.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest {
    TEST_CLASS(Tokenize) {
public:
    TEST_METHOD(findCommandTest) {
        CommandTokenizer ct;
        std::string input = "add #cs2103 #homework on 30th Sep";
        std::string expected = (std::string) "add";

        std::string obj = ct.findCommand(ParserLibrary::explode(input, " "));
        Assert::AreEqual(expected, obj);
    }

    TEST_METHOD(findTagsTest) {
        CommandTokenizer ct;
        std::string input = "add #cs2103 #homework on 30th Sep";
        std::string expected = (std::string) "{ homework, cs2103 }";

        std::vector<std::string> obj = ct.findTags(ParserLibrary::explode(input, " "));
        Assert::AreEqual(expected, ParserLibrary::vectorToString(obj));
    }

    TEST_METHOD(findDescriptionTest) {
        CommandTokenizer ct;
        std::string input = "add #cs2103 #homework on 30th Sep";
        std::string expected = (std::string) "#cs2103 #homework on 30th Sep";

        std::string obj = ct.findDescription(ParserLibrary::explode(input, " "));
        Assert::AreEqual(expected, obj);
    }

    TEST_METHOD(findDateTest) {
        CommandTokenizer ct;
        std::string input = "add #cs2103 #homework on 17th of March";
        std::string expected = (std::string) "{ 17-03-2016 }";
        std::string actual = "";

        std::vector<std::chrono::system_clock::time_point> obj = ct.findDate(ParserLibrary::explode(input, " "));

        Assert::AreEqual(expected, actual);
    }

    TEST_METHOD(toDateFormatTest1) {
        CommandTokenizer ct;
        std::string input = "March 17 2015";
        std::string expected = "17/3/2015";
        std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");
        std::tm time = ct.toDateFormat(inputArr);
        std::string actual = std::to_string(time.tm_mday) + "/" + std::to_string(time.tm_mon+1) + "/" + std::to_string(time.tm_year + 1900);

        Assert::AreEqual(expected, actual);
    }

    TEST_METHOD(toDateFormatTest2) {
        CommandTokenizer ct;
        std::string input = "March 17";
        std::string expected = "17/3/2015";
        std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");
        std::tm time = ct.toDateFormat(inputArr);
        std::string actual = std::to_string(time.tm_mday) + "/" + std::to_string(time.tm_mon+1) + "/" + std::to_string(time.tm_year + 1900);

        Assert::AreEqual(expected, actual);
    }

    TEST_METHOD(toDateFormatTest3) {
        CommandTokenizer ct;
        std::string input = "17th";
        std::string expected = "17/10/2015";
        std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");
        std::tm time = ct.toDateFormat(inputArr);
        std::string actual = std::to_string(time.tm_mday) + "/" + std::to_string(time.tm_mon+1) + "/" + std::to_string(time.tm_year + 1900);

        Assert::AreEqual(expected, actual);
    }

    TEST_METHOD(toDateFormatTest4) {
        CommandTokenizer ct;
        std::string input = "March 17th 2015";
        std::string expected = "17/3/2015";
        std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");
        std::tm time = ct.toDateFormat(inputArr);
        std::string actual = std::to_string(time.tm_mday) + "/" + std::to_string(time.tm_mon+1) + "/" + std::to_string(time.tm_year + 1900);

        Assert::AreEqual(expected, actual);
    }

    TEST_METHOD(toDateFormatTest5) {
        CommandTokenizer ct;
        std::string input = "March 17th 20150";
        std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");

        bool assertion = false;
        try {
            std::tm time = ct.toDateFormat(inputArr);
            std::string actual = std::to_string(time.tm_mday) + "/" + std::to_string(time.tm_mon + 1) + "/" + std::to_string(time.tm_year + 1900);
        } catch (std::invalid_argument e) {
            assertion = true;
        }
        Assert::IsTrue(assertion);
    }

    TEST_METHOD(toDateFormatTest6) {
        CommandTokenizer ct;
        std::string input = "March";
        std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");

        bool assertion = false;
        try {
            std::tm time = ct.toDateFormat(inputArr);
            std::string actual = std::to_string(time.tm_mday) + "/" + std::to_string(time.tm_mon + 1) + "/" + std::to_string(time.tm_year + 1900);
        } catch (std::invalid_argument e) {
            assertion = true;
        }
        Assert::IsTrue(assertion);
    }

    TEST_METHOD(explodeTest) {
        std::string input = "17th";
        std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");
        Assert::AreEqual(input, inputArr.at(0));
    }


    std::string test(std::string input) {
        std::string dayAppendixPattern = "(st|nd|rd|th)$";
        input = std::regex_replace(input, std::regex(dayAppendixPattern), "");

        if (input.length() > 2) {
            return "(1) " + input;
        } else if (input.at(1) > '9' || input.at(1) < '0') {
            return "(2) " + input.at(0);
        } else if (input.at(0) > '3' || input.at(1) < '0') {
            return "(3) " + input;
        }
        return input;
    }

    TEST_METHOD(generalTest) {
        CommandTokenizer ct;
        std::string input = "17th";
        std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");
        std::string expected = "17";
        Assert::AreEqual(expected, test(input));
    }


    };
}


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

    TEST_METHOD(isDMYDateFormatTest1) {
        CommandTokenizer ct;
        std::string input = "17th March 2015";
        std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");
        Assert::IsTrue(ct.isDateFormat(inputArr));
    }

    TEST_METHOD(isDMYDateFormatTest2) {
        CommandTokenizer ct;
        std::string input = "17th March";
        std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");
        Assert::IsTrue(ct.isDateFormat(inputArr));
    }

    TEST_METHOD(isDMYDateFormatTest3) {
        CommandTokenizer ct;
        std::string input = "17th";
        std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");
        Assert::IsTrue(ct.isDateFormat(inputArr));
    }

    TEST_METHOD(isDMYDateFormatTest4) {
        CommandTokenizer ct;
        std::string input = "March";
        std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");
        Assert::IsFalse(ct.isDateFormat(inputArr));
    }

    TEST_METHOD(isDMYDateFormatTest5) {
        CommandTokenizer ct;
        std::string input = "March 17th 2015";
        std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");
        Assert::IsTrue(ct.isDateFormat(inputArr));
    }

    TEST_METHOD(isDMYDateFormatTest6) {
        CommandTokenizer ct;
        std::string input = "March 17wow 2015";
        std::vector<std::string> inputArr = ParserLibrary::explode(input, " ");
        Assert::IsFalse(ct.isDateFormat(inputArr));
    }



    TEST_METHOD(findDateTest) {
        CommandTokenizer ct;
        std::string input = "add #cs2103 #homework on 17th of March";
        std::string expected = (std::string) "{ 17-03-2016 }";
        std::string actual = "";
        
        std::vector<std::chrono::system_clock::time_point> obj = ct.findDate(ParserLibrary::explode(input, " "));

        Assert::AreEqual(expected, actual);
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


#include "stdafx.h"
#include "CppUnitTest.h"
#include "regex"
#include <iterator>

#include "basic.h"

#include "CommandTokenizer.h"
#include "ParserLibrary.h"
#include "DateTimeParser.h"
#include "CommandParser.h"

#include "Commands/Command.h"
#include "Models/Task.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest {
    TEST_CLASS(Tokenize) {
public:
    void parseAddTestMethod(std::string input, std::vector<std::string> expected) {
        try {
            std::vector<std::string> inputArr = DoLah::ParserLibrary::explode(input, " ");
            std::string command = DoLah::CommandTokenizer::findCommand(inputArr);
            std::vector<std::tm> datesVector = DoLah::CommandTokenizer::findDate(inputArr);
            std::string dates = "";
            if (!datesVector.empty()) {
                dates = DoLah::DateTimeParser::tmToString(datesVector.at(0));
            }
            std::string tags = DoLah::ParserLibrary::vectorToString(DoLah::CommandTokenizer::findTags(inputArr));
            std::string description = DoLah::CommandTokenizer::findDescription(inputArr);

            std::vector<std::string> actual = { command, dates, tags, description };
            AreEqualStringVectors(expected, actual);
        } catch (std::exception e) {
            std::string message = e.what();
            Assert::AreEqual(message, expected.at(0));
        }
    }

    void AreEqualStringVectors(std::vector<std::string> expected, std::vector<std::string> actual) {
        for (size_t i = 0; i < expected.size(); i++) {
            Assert::AreEqual(actual.at(i), expected.at(i));
        }
    }

    TEST_METHOD(parseAddTest1) {
        parseAddTestMethod((std::string)
            "add #cs2103 #homework on 30th",
            { "add", "30/10/2015", "{ homework, cs2103 }", "#cs2103 #homework" }
        );
    }

    TEST_METHOD(parseAddTest2) {
        parseAddTestMethod((std::string)
            "add #cs2103 #homework on 300th",
            { "add", "", "{ homework, cs2103 }", "#cs2103 #homework on 300th" }
        );
    }

    TEST_METHOD(parseAddTest3) {
        parseAddTestMethod((std::string)
            "addd #cs2103 #homework on 300th",
            { "command not recognized" }
        );
    }

    };
}


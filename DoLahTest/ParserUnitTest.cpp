#include "stdafx.h"
#include "CppUnitTest.h"
#include "regex"
#include <iterator>

#include "ParserLibrary.h"
#include "CommandParser.h"
#include "CommandTokenizer.h"
#include "TaskParser.h"
#include "TaskTokenizer.h"
#include "DateTimeParser.h"

#include "Commands/Command.h"
#include "Models/Task.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest {
    TEST_CLASS(Tokenize) {
public:
    void parseAddTestMethod(std::string input, std::vector<std::string> expected) {
        try {
            std::vector<std::string> inputArr = DoLah::ParserLibrary::explode(input, " ");
            std::vector<std::tm> datesVector = DoLah::TaskTokenizer::findDate(inputArr);
            std::string dates = "";
            if (!datesVector.empty()) {
                dates = DoLah::DateTimeParser::tmToString(datesVector.at(0));
            }
            std::string tags = DoLah::ParserLibrary::vectorToString(DoLah::TaskTokenizer::findTags(inputArr));
            std::string description = DoLah::TaskTokenizer::findDescription(inputArr);

            std::vector<std::string> actual = { dates, tags, description };
            AreEqualStringVectors(expected, actual);
        } catch (std::exception e) {
            throw e;
        }
    }

    void AreEqualStringVectors(std::vector<std::string> expected, std::vector<std::string> actual) {
        for (size_t i = 0; i < expected.size(); i++) {
            Assert::AreEqual(expected.at(i), actual.at(i));
        }
    }

    TEST_METHOD(parseAddDetailedTest1) {
        parseAddTestMethod((std::string)
            "#cs2103 #homework on 30th",
            { "30/10/2015", "{ homework, cs2103 }", "#cs2103 #homework" }
        );
    }

    TEST_METHOD(parseAddDetailedTest2) {
        parseAddTestMethod((std::string)
            "#cs2103 #homework on 300th",
            { "", "{ homework, cs2103 }", "#cs2103 #homework on 300th" }
        );
    }

    TEST_METHOD(parseAddDetailedTest3) {
        parseAddTestMethod((std::string)
            "#cs2103 #homework on December 25th 2015",
            { "25/12/2015", "{ homework, cs2103 }", "#cs2103 #homework" }
        );
    }

    TEST_METHOD(parseAddDetailedTest4) {
        parseAddTestMethod((std::string)
            "#cs2103 #homework on the #stage",
            { "", "{ stage, homework, cs2103 }", "#cs2103 #homework on the #stage" }
        );
    }

    std::string UNHANDLED_COMMAND_MESSAGE = "Command not handled";
    std::string UNKNOWN_COMMAND_MESSAGE = "Command not recognized";
    std::string TOO_MANY_ARGUMENTS_MESSAGE = "Too many arguments";
    std::string TOO_LITTLE_ARGUMENTS_MESSAGE = "Too little arguments";
    std::string INVALID_TASK_ID_ARGUMENT = "Invalid edit argument";

    TEST_METHOD(parseAddTest1) {
        std::string input = "added #cs2103 #homework on the #stage";

        bool flag = false;
        try {
            DoLah::CommandParser::parse(input);
        } catch (std::invalid_argument e) {
            std::string message = e.what();
            Assert::AreEqual(UNKNOWN_COMMAND_MESSAGE, message);
            flag = true;
        }
        if (!flag) {
            Assert::IsFalse(true);
        }
    }

    TEST_METHOD(parseEditTest1) {
        std::string input = "edit #cs2103 #homework on the #stage";

        bool flag = false;
        try {
            DoLah::CommandParser::parse(input);
        } catch (std::invalid_argument e) {
            std::string message = e.what();
            Assert::AreEqual(INVALID_TASK_ID_ARGUMENT, message);
            flag = true;
        }
        if (!flag) {
            Assert::IsFalse(true);
        }
    }

    TEST_METHOD(parseEditTest2) {
        std::string input = "edit 100 #cs2103 #homework on the #stage";

        bool flag = false;
        try {
            DoLah::CommandParser::parse(input);
        } catch (std::invalid_argument e) {
            flag = true;
        }
        Assert::IsFalse(flag);
    }

    TEST_METHOD(parseSearchTest1) {
        std::string input = "search me";

        bool flag = false;
        try {
            DoLah::CommandParser::parse(input);
        } catch (std::invalid_argument e) {
            std::string message = e.what();
            Assert::AreEqual(INVALID_TASK_ID_ARGUMENT, message);
            flag = true;
        }
        Assert::IsFalse(flag);
    }

    TEST_METHOD(parseSearchTest2) {
        std::string input = "search ";

        bool flag = false;
        try {
            DoLah::CommandParser::parse(input);
        } catch (std::invalid_argument e) {
            std::string message = e.what();
            Assert::AreEqual(TOO_LITTLE_ARGUMENTS_MESSAGE, message);
            flag = true;
        }
        if (!flag) {
            Assert::IsFalse(true);
        }
    }

    TEST_METHOD(parseDeleteTest1) {
        std::string input = "delete me";

        bool flag = false;
        try {
            DoLah::CommandParser::parse(input);
        } catch (std::invalid_argument e) {
            std::string message = e.what();
            Assert::AreEqual(INVALID_TASK_ID_ARGUMENT, message);
            flag = true;
        }
        if (!flag) {
            Assert::IsFalse(true);
        }
    }

    TEST_METHOD(parseClearTest1) {
        std::string input = "clear me";

        bool flag = false;
        try {
            DoLah::CommandParser::parse(input);
        } catch (std::invalid_argument e) {
            std::string message = e.what();
            Assert::AreEqual(TOO_MANY_ARGUMENTS_MESSAGE, message);
            flag = true;
        }
        if (!flag) {
            Assert::IsFalse(true);
        }
    }

    TEST_METHOD(stripTest) {
        std::string input = " search ";
        std::string expected = "search";
        std::string actual = DoLah::ParserLibrary::strip(input);
        Assert::AreEqual(expected, actual);
    }

    TEST_METHOD(equalitytest) {
        std::string input = " search ";
        Assert::IsTrue(input.at(0) == ' ');
    }

    };
}


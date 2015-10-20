#include "stdafx.h"
#include "CppUnitTest.h"
#include "regex"
#include <iterator>

#include "Parser/ParserLibrary.h"
#include "Parser/CommandParser.h"
#include "Parser/CommandTokenizer.h"
#include "Parser/TaskParser.h"
#include "Parser/TaskTokenizer.h"
#include "Parser/DateTimeParser.h"

#include "Commands/Command.h"
#include "Models/Task.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest {
    TEST_CLASS(Parser) {
private:
    std::string year;
    std::string month;
    std::string day;
public:
    std::string tmToString(std::tm time) {
        return std::to_string(time.tm_mday) + "/"
            + std::to_string(time.tm_mon + 1) + "/"
            + std::to_string(time.tm_year + 1900);
    }
    void parseAddTestMethod(std::string input, std::vector<std::string> expected) {
        try {
            std::vector<std::string> inputArr = DoLah::ParserLibrary::explode(input, " ");
            std::vector<std::tm> datesVector = DoLah::TaskTokenizer::findAndRemoveDate(inputArr);
            std::string dates = "";
            if (!datesVector.empty()) {
                for (size_t i = 0; i < datesVector.size(); i++) {
                    dates += tmToString(datesVector.at(i));
                    if (i < datesVector.size() - 1) {
                        dates += " ~ ";
                    }
                }
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

    std::string UNHANDLED_COMMAND_MESSAGE = "Command not handled";
    std::string UNKNOWN_COMMAND_MESSAGE = "Command not recognized";
    std::string TOO_MANY_ARGUMENTS_MESSAGE = "Too many arguments";
    std::string TOO_LITTLE_ARGUMENTS_MESSAGE = "Too little arguments";
    std::string INVALID_TASK_ID_ARGUMENT = "Invalid task ID given";

    std::string UNEXPECTED_EXCEPTION = "This is an unexpected exception.";

    TEST_METHOD_INITIALIZE(Startup) {
        time_t t = time(0);
        std::tm current;
        localtime_s(&current, &t);
        year = std::to_string(current.tm_year + 1900);
        month = std::to_string(current.tm_mon + 1);
        day = std::to_string(current.tm_mday);
    }

    TEST_METHOD(parseExceptionTest1) {
        std::string input = "eddard ";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(UNKNOWN_COMMAND_MESSAGE, (std::string) e.what());
        }
    }

    TEST_METHOD(parseExceptionTest2) {
        std::string input = "sort ";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(UNHANDLED_COMMAND_MESSAGE, (std::string) e.what());
        }
    }

    TEST_METHOD(parseAddTest) {
        std::string input = "add #cs2103 #homework on 30th December 2015";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(true);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(UNEXPECTED_EXCEPTION, (std::string) e.what());
        }
    }

    TEST_METHOD(parseAddExceptionTest) {
        std::string input = "add ";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(TOO_LITTLE_ARGUMENTS_MESSAGE, (std::string) e.what());
        }
    }

    TEST_METHOD(parseEditTest) {
        std::string input = "edit 100 #cs2103 #homework on the #stage";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(true);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(UNEXPECTED_EXCEPTION, (std::string) e.what());
        }
    }

    TEST_METHOD(parseEditExceptionTest1) {
        std::string input = "edit #cs2103 #homework on the #stage";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(INVALID_TASK_ID_ARGUMENT, (std::string) e.what());
        }
    }

    TEST_METHOD(parseEditExceptionTest2) {
        std::string input = "edit 100";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(TOO_LITTLE_ARGUMENTS_MESSAGE, (std::string) e.what());
        }
    }

    TEST_METHOD(parseSearchTest) {
        std::string input = "search me";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(true);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(UNEXPECTED_EXCEPTION, (std::string) e.what());
        }
    }

    TEST_METHOD(parseSearchExceptionTest) {
        std::string input = "search ";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(TOO_LITTLE_ARGUMENTS_MESSAGE, (std::string) e.what());
        }
    }

    TEST_METHOD(parseDeleteTest) {
        std::string input = "delete 100";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(true);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(UNEXPECTED_EXCEPTION, (std::string) e.what());
        }
    }

    TEST_METHOD(parseDeleteExceptionTest1) {
        std::string input = "delete 100 wow";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(TOO_MANY_ARGUMENTS_MESSAGE, (std::string) e.what());
        }
    }

    TEST_METHOD(parseDeleteExceptionTest2) {
        std::string input = "delete wow";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(INVALID_TASK_ID_ARGUMENT, (std::string) e.what());
        }
    }

    TEST_METHOD(parseDeleteExceptionTest3) {
        std::string input = "delete ";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(TOO_LITTLE_ARGUMENTS_MESSAGE, (std::string) e.what());
        }
    }

    TEST_METHOD(parseClearTest) {
        std::string input = "clear ";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(true);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(UNEXPECTED_EXCEPTION, (std::string) e.what());
        }
    }

    TEST_METHOD(parseClearExceptionTest) {
        std::string input = "clear wow";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(TOO_MANY_ARGUMENTS_MESSAGE, (std::string) e.what());
        }
    }

    TEST_METHOD(parseUndoTest) {
        std::string input = "undo ";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(true);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(UNEXPECTED_EXCEPTION, (std::string) e.what());
        }
    }

    TEST_METHOD(parseUndoExceptionTest) {
        std::string input = "undo wow";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(TOO_MANY_ARGUMENTS_MESSAGE, (std::string) e.what());
        }
    }

    // parseAdd()
    // input in string
    // expect in { string date, vector<string> tags, string name }
    TEST_METHOD(parseAddDetailedTest1) {
        parseAddTestMethod((std::string)
            "task",
            { "", "{  }", "task" }
        );
    }

    TEST_METHOD(parseAddDetailedTest2) {
        parseAddTestMethod((std::string)
            "task on 24.12.2015",
            { "24/12/2015", "{  }", "task" }
        );
    }

    TEST_METHOD(parseAddDetailedTest3) {
        parseAddTestMethod((std::string)
            "task by 24.12.2015",
            { "24/12/2015", "{  }", "task" }
        );
    }

    TEST_METHOD(parseAddDetailedTest4) {
        parseAddTestMethod((std::string)
            "task from 24.12.2015 to 25.12.2015",
            { "24/12/2015 ~ 25/12/2015", "{  }", "task" }
        );
    }

    TEST_METHOD(parseAddDetailedTest5) {
        parseAddTestMethod((std::string)
            "task from 24.12.2015 until 25.12.2015",
            { "24/12/2015 ~ 25/12/2015", "{  }", "task" }
        );
    }

    TEST_METHOD(parseAddDetailedTest6) {
        parseAddTestMethod((std::string)
            "#task from 24.12.2015 until 25.12.2015",
            { "24/12/2015 ~ 25/12/2015", "{ task }", "#task" }
        );
    }

    TEST_METHOD(parseAddDetailedTest7) {
        parseAddTestMethod((std::string)
            "#cs2103 #task from 24.12.2015 until 25.12.2015",
            { "24/12/2015 ~ 25/12/2015", "{ task, cs2103 }", "#cs2103 #task" }
        );
    }

    TEST_METHOD(parseAddDetailedTest8) {
        parseAddTestMethod((std::string)
            "task on 24th of December 20150",
            { "", "{  }", "task on 24th of December 20150" }
        );
    }

    TEST_METHOD(parseAddDetailedTest9) {
        parseAddTestMethod((std::string)
            "task on 24th of Decemberu",
            { "", "{  }", "task on 24th of Decemberu" }
        );
    }

    TEST_METHOD(parseAddDetailedTest10) {
        parseAddTestMethod((std::string)
            "task on 24the",
            { "", "{  }", "task on 24the" }
        );
    }

    TEST_METHOD(parseAddDetailedTest11) {
        parseAddTestMethod((std::string)
            "task on December",
            { "", "{  }", "task on December" }
        );
    }

    TEST_METHOD(parseAddDetailedTest12) {
        parseAddTestMethod((std::string)
            "task on Decemberu",
            { "", "{  }", "task on Decemberu" }
        );
    }

    TEST_METHOD(parseAddDetailedTest13) {
        parseAddTestMethod((std::string)
            "task on December 24the",
            { "", "{  }", "task on December 24the" }
        );
    }

    TEST_METHOD(parseAddDetailedTest14) {
        parseAddTestMethod((std::string)
            "task on December 24th 20150",
            { "", "{  }", "task on December 24th 20150" }
        );
    }

    TEST_METHOD(toDateFormatTest1) {
        std::string input = "1st January 2015";
        std::string expected = "1/1/2015";
        std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
        Assert::AreEqual(expected, actual);
    }

    TEST_METHOD(toDateFormatTest2) {
        std::string input = "1st January";
        std::string expected = "1/1/" + year;
        std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
        Assert::AreEqual(expected, actual);
    }

    TEST_METHOD(toDateFormatTest3) {
        std::string input = "1st";
        std::string expected = "1/" + month + "/" + year;
        std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
        Assert::AreEqual(expected, actual);
    }

    TEST_METHOD(toDateFormatTest4) {
        std::string input = "January 1st 2015";
        std::string expected = "1/1/2015";
        std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
        Assert::AreEqual(expected, actual);
    }

    TEST_METHOD(toDateFormatTest5) {
        std::string input = "January 1st";
        std::string expected = "1/1/" + year;
        std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
        Assert::AreEqual(expected, actual);
    }

    TEST_METHOD(toDateFormatTest6) {
        std::string input = "1st Jan 2015";
        std::string expected = "1/1/2015";
        std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
        Assert::AreEqual(expected, actual);
    }

    TEST_METHOD(toDateFormatTest7) {
        std::string input = "24.12.2015";
        std::string expected = "24/12/2015";
        std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
        Assert::AreEqual(expected, actual);
    }

    TEST_METHOD(toDateFormatTest8) {
        std::string input = "12.24.2015";
        std::string expected = "24/12/2015";
        std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
        Assert::AreEqual(expected, actual);
    }

    TEST_METHOD(toDateFormatTest9) {
        std::string input = "12.24.15";
        std::string expected = "24/12/2015";
        std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
        Assert::AreEqual(expected, actual);
    }

    std::string REJECT = "-1";

    TEST_METHOD(getDayExceptionTest1) {
        std::string input = "1str";
        std::string expected = REJECT;
        Assert::AreEqual(expected, std::to_string(DoLah::DateTimeParser::getDay(input)));
    }

    TEST_METHOD(getDayExceptionTest2) {
        std::string input = "me";
        std::string expected = REJECT;
        Assert::AreEqual(expected, std::to_string(DoLah::DateTimeParser::getDay(input)));
    }

    TEST_METHOD(getDayExceptionTest3) {
        std::string input = "10000";
        std::string expected = REJECT;
        Assert::AreEqual(expected, std::to_string(DoLah::DateTimeParser::getDay(input)));
    }

    TEST_METHOD(getMonthExceptionTest1) {
        std::string input = "christmas";
        std::string expected = REJECT;
        Assert::AreEqual(expected, std::to_string(DoLah::DateTimeParser::getMonth(input)));
    }

    TEST_METHOD(getMonthExceptionTest2) {
        std::string input = "10000";
        std::string expected = REJECT;
        Assert::AreEqual(expected, std::to_string(DoLah::DateTimeParser::getMonth(input)));
    }

    TEST_METHOD(getYearExceptionTest1) {
        std::string input = "10000";
        std::string expected = REJECT;
        Assert::AreEqual(expected, std::to_string(DoLah::DateTimeParser::getYear(input)));
    }

    TEST_METHOD(getYearExceptionTest2) {
        std::string input = "four";
        std::string expected = REJECT;
        Assert::AreEqual(expected, std::to_string(DoLah::DateTimeParser::getYear(input)));
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


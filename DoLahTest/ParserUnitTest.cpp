#include "stdafx.h"
#include "CppUnitTest.h"
#include "regex"
#include <iterator>
#include <functional>
#include <stdexcept>

#include "Parser/ParserLibrary.h"
#include "Parser/CommandParser.h"
#include "Parser/CommandTokenizer.h"
#include "Parser/TaskParser.h"
#include "Parser/TaskTokenizer.h"
#include "Parser/DateTimeParser.h"

#include "Commands/Command.h"
#include "Models/Task.h"

#include "CalendarBuilder.h"
#include "TaskBuilder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest {
    TEST_CLASS(Parser) {
private:
    std::string year;
    std::string month;
    std::string day;
public:
    void parseAddTestMethod(std::string input, std::vector<std::string> expected) {
        try {
            std::vector<std::string> inputArr = DoLah::ParserLibrary::explode(input, " ");
            std::vector<std::tm> datesVector = DoLah::TaskTokenizer::findAndRemoveDate(inputArr);
            std::string dates = "";
            if (!datesVector.empty()) {
                for (size_t i = 0; i < datesVector.size(); i++) {
                    dates += std::to_string(datesVector.at(i).tm_mday) + "/"
                        + std::to_string(datesVector.at(i).tm_mon + 1) + "/"
                        + std::to_string(datesVector.at(i).tm_year + 1900);
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

    TEST_METHOD_INITIALIZE(Startup) {
        time_t t = time(0);
        std::tm current;
        localtime_s(&current, &t);
        year = std::to_string(current.tm_year + 1900);
        month = std::to_string(current.tm_mon + 1);
        day = std::to_string(current.tm_mday);
    }

    TEST_METHOD(parseAddDetailedTest1) {
        parseAddTestMethod((std::string)
            "#cs2103 #homework on 30th",
            { "30/" + month + "/" + year, "{ homework, cs2103 }", "#cs2103 #homework" }
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

    TEST_METHOD(parseAddDetailedTest5) {
        parseAddTestMethod((std::string)
            "#cs2103 #homework on the #stage from 15th to 21st",
            { "15/" + month + "/" + year + " ~ 21/" + month + "/" + year, "{ stage, homework, cs2103 }", "#cs2103 #homework on the #stage" }
        );
    }

    TEST_METHOD(parseAddDetailedTest6) {
        parseAddTestMethod((std::string)
            "workout from 15th of Nov to 21st of Dec",
            { "15/11/" + year + " ~ 21/12/" + year, "{  }", "workout" }
        );
    }

    TEST_METHOD(parseAddDetailedTest7) {
        parseAddTestMethod((std::string)
            "workout from 10-18-2015 to 10-25-2015",
            { "18/10/2015 ~ 25/10/2015", "{  }", "workout" }
        );
    }

    TEST_METHOD(getMonthTest1) {
        Assert::AreEqual((std::string) "1", std::to_string(DoLah::DateTimeParser::getMonth("feb")));
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

    TEST_METHOD(ParseSetDoneCommand) {

        // Arrange
        std::string input = "done 1";

        // Act
        DoLah::ITaskCommand* cmd = DoLah::CommandParser::parse(input);

        // Assert
        Assert::AreEqual(typeid(DoLah::SetDoneTaskCommand).name(), typeid(*cmd).name());
    }

    TEST_METHOD(ParseIncompleteSetDoneCommand) {

        // Arrange
        std::string input = "done";

        // Act
        std::function<DoLah::ITaskCommand* (void)> func = [input] {
            return DoLah::CommandParser::parse(input);
        };

        // Assert
        Assert::ExpectException<std::invalid_argument>(func);
    }

    TEST_METHOD(ParseTooManyArgumentSetDoneCommand) {

        // Arrange
        std::string input = "done task 1";

        // Act
        std::function<DoLah::ITaskCommand* (void)> func = [input] {
            return DoLah::CommandParser::parse(input);
        };

        // Assert
        Assert::ExpectException<std::invalid_argument>(func);
    }

    TEST_METHOD(ParseInvalidArgumentSetDoneCommand) {

        // Arrange
        std::string input = "done -1";

        // Act
        std::function<DoLah::ITaskCommand* (void)> func = [input] {
            return DoLah::CommandParser::parse(input);
        };

        // Assert
        Assert::ExpectException<std::invalid_argument>(func);
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


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
    void parseTaskMethod(std::string input, std::vector<std::string> expected) {
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

    TEST_METHOD(DateGivenDayAndMonth) {
        std::string input = "2st January";
        std::string expected = "2/1/" + year;
        std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
        Assert::AreEqual(expected, actual);
    }

    TEST_METHOD(DateGivenDay) {
        std::string input = "1st";
        std::string expected = "1/" + month + "/" + year;
        std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
        Assert::AreEqual(expected, actual);
    }

    TEST_METHOD(DateGivenMonthAndDay) {
        std::string input = "January 2st";
        std::string expected = "2/1/" + year;
        std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
        Assert::AreEqual(expected, actual);
    }

    TEST_METHOD(DateInDifferentFormat1) {
        std::string input = "24.12.2015";
        std::string expected = "24/12/2015";
        std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
        Assert::AreEqual(expected, actual);
    }

    TEST_METHOD(DateInDifferentFormat2) {
        std::string input = "24-12-2015";
        std::string expected = "24/12/2015";
        std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
        Assert::AreEqual(expected, actual);
    }


    // parseAdd()
    // input in string
    // expect in { string date, vector<string> tags, string name }
    TEST_METHOD(FloatingWithName) {
        parseTaskMethod((std::string)
            "task",
            { "", "{  }", "task" }
        );
    }

    TEST_METHOD(DeadlineWithName) {
        parseTaskMethod((std::string)
            "task on 24.12.2015",
            { "24/12/2015", "{  }", "task" }
        );
    }

    TEST_METHOD(EventWithName) {
        parseTaskMethod((std::string)
            "task from 24.12.2015 to 25.12.2015",
            { "24/12/2015 ~ 25/12/2015", "{  }", "task" }
        );
    }

    TEST_METHOD(EventWithNameAndTag) {
        parseTaskMethod((std::string)
            "#task from 24.12.2015 until 25.12.2015",
            { "24/12/2015 ~ 25/12/2015", "{ task }", "#task" }
        );
    }

    TEST_METHOD(EventWithNameAndMultipleTags) {
        parseTaskMethod((std::string)
            "#cs2103 #task from 24.12.2015 until 25.12.2015",
            { "24/12/2015 ~ 25/12/2015", "{ task, cs2103 }", "#cs2103 #task" }
        );
    }

    TEST_METHOD(WrongYearInDMY) {
        parseTaskMethod((std::string)
            "task on 24th of December 20150",
            { "", "{  }", "task on 24th of December 20150" }
        );
    }

    TEST_METHOD(WrongMonthInDMY) {
        parseTaskMethod((std::string)
            "task on 24th of Decemberu",
            { "", "{  }", "task on 24th of Decemberu" }
        );
    }

    TEST_METHOD(WrongDayInDMY) {
        parseTaskMethod((std::string)
            "task on 24the",
            { "", "{  }", "task on 24the" }
        );
    }

    TEST_METHOD(MonthWithoutDayInMDY) {
        parseTaskMethod((std::string)
            "task on December",
            { "", "{  }", "task on December" }
        );
    }

    TEST_METHOD(WrongMonthInMDY) {
        parseTaskMethod((std::string)
            "task on Decemberu 24th",
            { "", "{  }", "task on Decemberu 24th" }
        );
    }

    TEST_METHOD(WrongDayInMDY) {
        parseTaskMethod((std::string)
            "task on December 24the",
            { "", "{  }", "task on December 24the" }
        );
    }

    TEST_METHOD(WrongYearInMDY) {
        parseTaskMethod((std::string)
            "task on December 24th 20150",
            { "", "{  }", "task on December 24th 20150" }
        );
    }

    TEST_METHOD(ParseWrongCommandTest) {
        std::string input = "eddard ";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(UNKNOWN_COMMAND_MESSAGE, (std::string) e.what());
        }
    }

    TEST_METHOD(ParseUnimplementedCommandTest) {
        std::string input = "sort ";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(UNHANDLED_COMMAND_MESSAGE, (std::string) e.what());
        }
    }

    TEST_METHOD(WellDefinedAddCommandWithDeadline) {
        std::string input = "add #cs2103 #homework on 30th December 2015";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(true);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(UNEXPECTED_EXCEPTION, (std::string) e.what());
        }
    }

    TEST_METHOD(WellDefinedAddCommandWithEvent) {
        std::string input = "add #cs2103 #homework from 30th Dec 2015 to 31st Dec 2015";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(true);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(UNEXPECTED_EXCEPTION, (std::string) e.what());
        }
    }

    TEST_METHOD(AddCommandWithoutDescription) {
        std::string input = "add ";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(TOO_LITTLE_ARGUMENTS_MESSAGE, (std::string) e.what());
        }
    }

    TEST_METHOD(WellDeginedEditCommand) {
        std::string input = "edit 100 #cs2103 #homework on the #stage";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(true);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(UNEXPECTED_EXCEPTION, (std::string) e.what());
        }
    }

    TEST_METHOD(EditCommandWithoutTaskIndex) {
        std::string input = "edit #cs2103 #homework on the #stage";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(INVALID_TASK_ID_ARGUMENT, (std::string) e.what());
        }
    }

    TEST_METHOD(EditCommandWithoutTaskDescription) {
        std::string input = "edit 100";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(TOO_LITTLE_ARGUMENTS_MESSAGE, (std::string) e.what());
        }
    }

    TEST_METHOD(WellDefinedSearchCommand) {
        std::string input = "search me";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(true);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(UNEXPECTED_EXCEPTION, (std::string) e.what());
        }
    }

    TEST_METHOD(SearchCommandWithoutDescription) {
        std::string input = "search ";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(TOO_LITTLE_ARGUMENTS_MESSAGE, (std::string) e.what());
        }
    }

    TEST_METHOD(WellDefinedDeleteCommand) {
        std::string input = "delete 100";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(true);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(UNEXPECTED_EXCEPTION, (std::string) e.what());
        }
    }

    TEST_METHOD(DeleteCommandWithTooManyArguments) {
        std::string input = "delete 100 wow";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(TOO_MANY_ARGUMENTS_MESSAGE, (std::string) e.what());
        }
    }

    TEST_METHOD(DeleteCommandWithWrongTaskIndex) {
        std::string input = "delete wow";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(INVALID_TASK_ID_ARGUMENT, (std::string) e.what());
        }
    }

    TEST_METHOD(DeleteCommandWithoutTaskIndex) {
        std::string input = "delete ";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(TOO_LITTLE_ARGUMENTS_MESSAGE, (std::string) e.what());
        }
    }

    TEST_METHOD(WellDefinedClearCommand) {
        std::string input = "clear ";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(true);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(UNEXPECTED_EXCEPTION, (std::string) e.what());
        }
    }

    TEST_METHOD(ClearCommandWithTooManyArguments) {
        std::string input = "clear wow";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(TOO_MANY_ARGUMENTS_MESSAGE, (std::string) e.what());
        }
    }

    TEST_METHOD(WellDefinedUndoCommand) {
        std::string input = "undo ";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(true);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(UNEXPECTED_EXCEPTION, (std::string) e.what());
        }
    }

    TEST_METHOD(UndoCommandWithTooManyArguments) {
        std::string input = "undo wow";
        try {
            DoLah::CommandParser::parse(input);
            Assert::IsTrue(false);
        } catch (std::invalid_argument e) {
            Assert::AreEqual(TOO_MANY_ARGUMENTS_MESSAGE, (std::string) e.what());
        }
    }

    };
}


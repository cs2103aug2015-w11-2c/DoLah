//@@collate A0116722M
#include "stdafx.h"
#include "CppUnitTest.h"
#include "regex"
#include <iterator>
#include <functional>
#include <stdexcept>

#include "Parser/ParserLibrary.h"
#include "Parser/CommandParser.h"
#include "Parser/TaskParser.h"
#include "Parser/TaskTokenizer.h"
#include "Parser/DateTimeParser.h"

#include "Commands/Command.h"
#include "Models/Task.h"

#include "CalendarBuilder.h"
#include "TaskBuilder.h"
#include "TimeManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest {
    TEST_CLASS(Parser) {
private:
    std::tm current;
    int year;
    int month;
    int day;
    int nextYear;
    int nextMonth;
    int nextDay;
    int hour;
    int min;
    int remainderDays;
public:
    std::string tmToString(std::tm time) {
        return ""
            + std::to_string(time.tm_hour) + ":"
            + std::to_string(time.tm_min) + ":"
            + std::to_string(time.tm_sec) + " "
            + std::to_string(time.tm_mday) + "/"
            + std::to_string(time.tm_mon + 1) + "/"
            + std::to_string(time.tm_year + 1900);
    }

    std::string strfyTime(int hour, int min, int sec, int day, int month, int year) {
        return ""
            + std::to_string(hour) + ":"
            + std::to_string(min) + ":"
            + std::to_string(sec) + " "
            + std::to_string(day) + "/"
            + std::to_string(month) + "/"
            + std::to_string(year)
            ;
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

    int getRemainderDaysOfTheMonth() {
        int count = 0;
        std::tm day = current;
        while (current.tm_mon == day.tm_mon) {
            day.tm_mday += 1;
            mktime(&day);
            count += 1;
        }

        return count - 1;
    }

    std::string UNHANDLED_COMMAND_MESSAGE = "Command not handled";
    std::string UNKNOWN_COMMAND_MESSAGE = "Command not recognized";
    std::string TOO_MANY_ARGUMENTS_MESSAGE = "Too many arguments";
    std::string TOO_LITTLE_ARGUMENTS_MESSAGE = "Too little arguments";
    std::string INVALID_TASK_ID_ARGUMENT = "Invalid task ID given";

    std::string UNEXPECTED_EXCEPTION = "This is an unexpected exception.";

    TEST_METHOD_INITIALIZE(Startup) {
        current = DoLah::TimeManager::getCurrentTime();

        year = current.tm_year + 1900;
        nextYear = current.tm_year + 1900 + 1;
        month = current.tm_mon + 1;
        nextMonth = current.tm_mon + 1 + 1;
        day = current.tm_mday;
        nextDay = current.tm_mday + 1;
        hour = current.tm_hour;
        min = current.tm_min;

        remainderDays = getRemainderDaysOfTheMonth();
    }

    // From here, unit tests for time parsing
    // Test for corner cases.
    TEST_METHOD(DateInDifferentFormat1) {
        std::string input = "24.12.2015";
        std::string expected = strfyTime(23, 59, 0, 24, 12, 2015);
        std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
        Assert::AreEqual(expected, actual);
    }

    TEST_METHOD(DateInDifferentFormat2) {
        std::string input = "24-12-2015";
        std::string expected = strfyTime(23, 59, 0, 24, 12, 2015);
        std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
        Assert::AreEqual(expected, actual);
    }

    // From here, integrated tests for task parsing
    // Does test for combination of multiple inputs

    TEST_METHOD(FloatingWithName) {
        parseTaskMethod((std::string)
            "task",
            { "", "{  }", "task" }
        );
    }

    TEST_METHOD(DeadlineWithName) {
        parseTaskMethod((std::string)
            "task on 24.12.2015",
            { strfyTime(23, 59, 0, 24, 12, 2015), "{  }", "task" }
        );
    }

    TEST_METHOD(EventWithName) {
        parseTaskMethod((std::string)
            "task from 24.12.2015 to 25.12.2015",
            { strfyTime(23, 59, 0, 24, 12, 2015) + " ~ " + strfyTime(23, 59, 0, 25, 12, 2015), "{  }", "task" }
        );
    }

    TEST_METHOD(EventWithNameAndTag) {
        parseTaskMethod((std::string)
            "#task from 24.12.2015 until 25.12.2015",
            { strfyTime(23, 59, 0, 24, 12, 2015) + " ~ " + strfyTime(23, 59, 0, 25, 12, 2015), "{ task }", "#task" }
        );
    }

    TEST_METHOD(EventWithNameAndMultipleTags) {
        parseTaskMethod((std::string)
            "#cs2103 #task from 24.12.2015 until 25.12.2015",
            { strfyTime(23, 59, 0, 24, 12, 2015) + " ~ " + strfyTime(23, 59, 0, 25, 12, 2015), "{ task, cs2103 }", "#cs2103 #task" }
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


    // From here, integrated tests for command parsing
    // Will check boundary cases and exceptions.
    // The actual content of the commands are hidden as black box.

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

    TEST_METHOD(WellDefinedEditCommand) {
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

    // From here, integrated test on special cases of 'toDateFormat' for relative time descriptions.
    // The time will auto-filled, and the behaviour changes depending on the time of running.
    // Test will be disabled in a certain condition where it cannot run properly.
    TEST_METHOD(DateGivenDayAndMonth) {
        if (month == 1 && day == 1) {
            Assert::IsTrue(true);
        } else { // test will not function in every new year
            std::string input = "1st January";
            std::string expected = strfyTime(23, 59, 0, 1, 1, nextYear);
            std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
            Assert::AreEqual(expected, actual);
        }
    }

    TEST_METHOD(DateGivenDay) {
        if (day == 1) {
            Assert::IsTrue(true);
        } else { // test will not function on the 1st of every month
            std::string input = "1st";
            std::string expected = strfyTime(23, 59, 0, 1, nextMonth, year);
            std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
            Assert::AreEqual(expected, actual);
        }
    }

    TEST_METHOD(DateGivenMonthAndDay) {
        if (month == 1 && day == 1) {
            Assert::IsTrue(true);
        } else { // test will not function in every new year
            std::string input = "January 1st";
            std::string expected = strfyTime(23, 59, 0, 1, 1, nextYear);
            std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
            Assert::AreEqual(expected, actual);
        }
    }

    TEST_METHOD(TestTomorrow) {
        if (remainderDays < 1) {
            Assert::IsTrue(true);
        } else { // test will not function on the last day of the month
            std::string input = "tomorrow";
            std::string expected = strfyTime(23, 59, 0, nextDay, month, year);
            std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
            Assert::AreEqual(expected, actual);
        }
    }

    TEST_METHOD(TestNextWeek) {
        if (remainderDays < 7) {
            Assert::IsTrue(true);
        } else { // test will not function on the last week of the month
            std::string input = "next week";
            std::string expected = strfyTime(23, 59, 0, day + 7, month, year);
            std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
            Assert::AreEqual(expected, actual);
        }
    }

    TEST_METHOD(TestIn2Days) {
        if (remainderDays < 2) {
            Assert::IsTrue(true);
        } else { // test will not function in the last 2 days of the month
            std::string input = "2 days";
            std::string expected = strfyTime(23, 59, 0, day + 2, month, year);
            std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
            Assert::AreEqual(expected, actual);
        }
    }

    TEST_METHOD(TestIn1Weeks) {
        if (remainderDays < 7) {
            Assert::IsTrue(true);
        } else { // test will not function in the last 1 weeks of the month
            std::string input = "1 week";
            std::string expected = strfyTime(23, 59, 0, day + 7, month, year);
            std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
            Assert::AreEqual(expected, actual);
        }
    }

    TEST_METHOD(TestAt1159PM) {
        if (hour == 23 && min == 59) {
            Assert::IsTrue(true);
        } else { // test will not function at 11:59:00
            std::string input = "11:59PM";
            std::string expected = strfyTime(23, 59, 0, day, month, year);
            std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
            Assert::AreEqual(expected, actual);
        }
    }

    TEST_METHOD(TestAt2359PM) {
        if (hour == 23 && min == 59) {
            Assert::IsTrue(true);
        } else { // test will not function at 11:59:00
            std::string input = "23:59PM";
            std::string expected = strfyTime(23, 59, 0, day, month, year);
            std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
            Assert::AreEqual(expected, actual);
        }
    }

    TEST_METHOD(TestAt2359) {
        if (hour == 23 && min == 59) {
            Assert::IsTrue(true);
        } else { // test will not function at 11:59:00
            std::string input = "23:59";
            std::string expected = strfyTime(23, 59, 0, day, month, year);
            std::string actual = tmToString(DoLah::DateTimeParser::toDateFormat(DoLah::ParserLibrary::explode(input, " ")));
            Assert::AreEqual(expected, actual);
        }
    }

    TEST_METHOD(ParseSetDoneCommand) {

        // Arrange
        std::string input = "done 1";

        // Act
        DoLah::AbstractCommand* cmd = DoLah::CommandParser::parse(input);

        // Assert
        Assert::AreEqual(typeid(DoLah::SetDoneTaskCommand).name(), typeid(*cmd).name());
    }

    TEST_METHOD(ParseIncompleteSetDoneCommand) {

        // Arrange
        std::string input = "done";

        // Act
        std::function<DoLah::AbstractCommand* (void)> func = [input] {
            return DoLah::CommandParser::parse(input);
        };

        // Assert
        Assert::ExpectException<std::invalid_argument>(func);
    }

    TEST_METHOD(ParseTooManyArgumentSetDoneCommand) {

        // Arrange
        std::string input = "done task 1";

        // Act
        std::function<DoLah::AbstractCommand* (void)> func = [input] {
            return DoLah::CommandParser::parse(input);
        };

        // Assert
        Assert::ExpectException<std::invalid_argument>(func);
    }

    TEST_METHOD(ParseInvalidArgumentSetDoneCommand) {

        // Arrange
        std::string input = "done -1";

        // Act
        std::function<DoLah::AbstractCommand* (void)> func = [input] {
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


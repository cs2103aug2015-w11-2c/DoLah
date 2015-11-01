#include "stdafx.h"
#include "CppUnitTest.h"

#include "Models/Task.h"
#include "Commands/Command.h"
#include "Models/Calendar.h"
#include "CalendarBuilder.h"
#include "TaskBuilder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest
{
    TEST_CLASS(CALENDAR_TESTER) {
    private:

    public:
        TEST_METHOD(AddTaskCommand) {
            //Arrange
            DoLah::Calendar testCal = DoLah::Calendar();
            DoLah::FloatingTask* task = TaskBuilder::buildFloatingTask();
            DoLah::AddTaskCommand addCommand = DoLah::AddTaskCommand(task);
            addCommand.setCalendar(&testCal);

            //Act
            addCommand.execute();

            //Assert
            Assert::AreEqual((size_t)1, testCal.getTaskList().size());
            Assert::AreEqual(task->getName(), testCal.getTaskList()[0]->getName());
            Assert::AreEqual(task->getDescription(), testCal.getTaskList()[0]->getDescription());
        }

        TEST_METHOD(DeleteTaskCommand) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
            int oldLength = testCal.getTaskList().size();
            DoLah::DeleteTaskCommand delCommand = DoLah::DeleteTaskCommand(4);
            delCommand.setCalendar(&testCal);

            //Act
            delCommand.execute();

            //Assert
            Assert::AreEqual((size_t)oldLength - 1, testCal.getTaskList().size());
        }

        TEST_METHOD(EditTaskCommand) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
            DoLah::DeadlineTask* task = TaskBuilder::buildDeadlineTask();
            DoLah::EditTaskCommand editCommand = DoLah::EditTaskCommand(0, task);
            editCommand.setCalendar(&testCal);

            //Act
            editCommand.execute();

            //Assert
            Assert::AreEqual(task->getName(), testCal.getTaskList()[0]->getName());
            Assert::AreEqual(task->getDescription(), testCal.getTaskList()[0]->getDescription());
            Assert::AreEqual(task->isDone(), testCal.getTaskList()[0]->isDone());
        }

        TEST_METHOD(ClearTaskCommand) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
            DoLah::ClearTaskCommand clearCommand = DoLah::ClearTaskCommand();
            clearCommand.setCalendar(&testCal);

            //Act
            clearCommand.execute();

            //Assert
            Assert::IsTrue(testCal.getTaskList().empty());
        }

        TEST_METHOD(SearchTaskCommand) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
            DoLah::SearchTaskCommand searchCommand = DoLah::SearchTaskCommand("Floating");
            searchCommand.setCalendar(&testCal);
            std::vector<DoLah::AbstractTask*> * resultVector = new std::vector<DoLah::AbstractTask*>;
            searchCommand.setResultVector(resultVector);
            
            //Act
            searchCommand.execute();

            //Assert
            Assert::AreEqual((size_t) 5, resultVector->size());
        }

        TEST_METHOD(UndoAddCommand) {

        }
    };
}
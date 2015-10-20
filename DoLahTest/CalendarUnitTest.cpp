#include "stdafx.h"
#include "CppUnitTest.h"

#include "Models/Task.h"
#include "Models/Calendar.h"
#include "CalendarBuilder.h"
#include "TaskBuilder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest
{		
	TEST_CLASS(CALENDAR_TESTER) {
	private:

    public:
        TEST_METHOD(AddTask) {
            //Arrange
            DoLah::Calendar testCal = DoLah::Calendar();
            DoLah::FloatingTask* task = TaskBuilder::buildFloatingTask();

            //Act
            testCal.addTask(task);

            //Assert
            Assert::AreEqual((size_t)1, testCal.getTaskList().size());
            Assert::AreEqual(task->getName(), testCal.getTaskList()[0]->getName());
            Assert::AreEqual(task->getDescription(), testCal.getTaskList()[0]->getDescription());
        }

        TEST_METHOD(DeleteTask) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
            int oldLength = testCal.getTaskList().size();

            //Act
            testCal.deleteTask(4);

            //Assert
            Assert::AreEqual((size_t)oldLength - 1, testCal.getTaskList().size());
        }

        TEST_METHOD(EditTask) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
            DoLah::DeadlineTask* task = TaskBuilder::buildDeadlineTask();

            //Act
            testCal.updateTask(0, task);

            //Assert
            Assert::AreEqual(task->getName(), testCal.getTaskList()[0]->getName());
            Assert::AreEqual(task->getDescription(), testCal.getTaskList()[0]->getDescription());
            Assert::AreEqual(task->isDone(), testCal.getTaskList()[0]->isDone());
        }

		TEST_METHOD(ClearTask) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
			
            //Act
            testCal.clearTasks();
			
            //Assert
            Assert::IsTrue(testCal.getTaskList().empty());
		}

		TEST_METHOD(FindTaskThatExists) {
			//Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();

            //Act
            std::vector<DoLah::AbstractTask*> resultVector = testCal.search("Floating");

            //Assert
            Assert::AreEqual((size_t)5, resultVector.size());
		}

        TEST_METHOD(FindTaskThatDoesNotExist) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();

            //Act
            std::vector<DoLah::AbstractTask*> resultVector = testCal.search("The quick brown fox");

            //Assert
            Assert::AreEqual((size_t)0, resultVector.size());
        }
	};
}
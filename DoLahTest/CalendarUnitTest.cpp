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
        TEST_METHOD(AddTask) {
            //Arrange
            DoLah::Calendar testCal = DoLah::Calendar();
            DoLah::FloatingTask* task = TaskBuilder::buildFloatingTask();

            //Act
            testCal.addTask(task);

            //Assert
            Assert::AreEqual(testCal.getTaskList().size(), (size_t) 1); 
            Assert::AreEqual(testCal.getTaskList()[0]->getName(), task->getName());
            Assert::AreEqual(testCal.getTaskList()[0]->getDescription(), task->getDescription());
        }

		TEST_METHOD(ClearTask) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
			
            //Act
            testCal.clearTasks();
			
            //Assert
            Assert::IsTrue(testCal.getTaskList().empty());
		}

		TEST_METHOD(SearchTask1) {
			testVector.erase(testVector.begin()+2);
			std::vector<DoLah::AbstractTask*> resultVector = testCal.search("homework");

			for (unsigned int i = 0; i < testVector.size(); i++) {
				Assert::AreEqual(testVector[i]->getName(), resultVector[i]->getName());
			}
		}

        TEST_METHOD(SearchTask2) {
            testVector.erase(testVector.begin() + 1);
            testVector.erase(testVector.begin());
            std::vector<DoLah::AbstractTask*> resultVector = testCal.search("practice");
        }
	};
}
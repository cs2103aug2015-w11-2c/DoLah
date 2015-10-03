#include "stdafx.h"
#include "CppUnitTest.h"

#include "basic.h"

#include "Models/Task.h"
#include "Commands/Command.h"
#include "Models/Calendar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest
{		
	TEST_CLASS(UnitTest1){
	public:
		
		TEST_METHOD(TestMethod1) {
            int result = add(1, 1);
            Assert::AreEqual(result, 2);
		}

	};

	TEST_CLASS(CALENDAR_TESTER) {
	private:
		DoLah::Calendar testCal;
		std::vector<DoLah::AbstractTask*> testVector;

	public:
		TEST_METHOD_INITIALIZE(Startup) {
			DoLah::FloatingTask* task1 = new DoLah::FloatingTask;
			task1->setName("Fly Me To The Moon");
			DoLah::FloatingTask* task2 = new DoLah::FloatingTask;
			task2->setName("And Let Me Play Among The Stars");
			DoLah::FloatingTask* task3 = new DoLah::FloatingTask;
			task3->setName("Let me see what spring is like");

			testVector.push_back(task1);
			testVector.push_back(task2);
			testVector.push_back(task3);

			for (int i = 0; i < testVector.size(); i++) {
				testCal.addTask(testVector.at(i));
			}

			testCal = DoLah::Calendar();
		}

		TEST_METHOD(AddTask) {
			/*for (int i = 0; i < testVector.size(); i++) {
				Assert::AreEqual(testVector.at(i), testCal.getTaskList().at(i));
			}*/
		}

		TEST_METHOD(ClearTask) {
			testCal.clearTasks();
			Assert::IsTrue(testCal.getTaskList().empty());
		}

	};
}
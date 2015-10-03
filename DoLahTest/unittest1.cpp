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
	public:

		TEST_METHOD(AddTask) {
			DoLah::FloatingTask* task1 = new DoLah::FloatingTask;
			task1->setName("Fly Me To The Moon");
			DoLah::FloatingTask* task2 = new DoLah::FloatingTask;
			task2->setName("And Let Me Play Among The Stars");
			DoLah::FloatingTask* task3 = new DoLah::FloatingTask;
			task3->setName("Let me see what spring is like");

			std::vector<DoLah::AbstractTask*> testVector;
			testVector.push_back(task1);
			testVector.push_back(task2);
			testVector.push_back(task3);


			DoLah::Calendar testCal = DoLah::Calendar();

			for (int i = 0; i < testVector.size(); i++) {
				testCal.addTask(testVector.at(i));
			}

			for (int i = 0; i < testVector.size(); i++) {
				Assert::AreSame(testVector.at(i), testCal.getTaskList().at(i));
			}
			
		}

	};
}
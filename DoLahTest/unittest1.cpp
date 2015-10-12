#include "stdafx.h"
#include "CppUnitTest.h"

#include "Models/Task.h"
#include "Commands/Command.h"
#include "Models/Calendar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest
{		
	TEST_CLASS(CALENDAR_TESTER) {
	private:
		std::vector<DoLah::AbstractTask*> testVector;
		DoLah::Calendar testCal;

	public:
		TEST_METHOD_INITIALIZE(Startup) {
			DoLah::FloatingTask* task1 = new DoLah::FloatingTask;
			task1->setName("CS2103 homework");
			DoLah::FloatingTask* task2 = new DoLah::FloatingTask;
			task2->setName("CS2101 homework");
			DoLah::FloatingTask* task3 = new DoLah::FloatingTask;
			task3->setName("singing practice");

			testVector.push_back(task1);
			testVector.push_back(task2);
			testVector.push_back(task3);

			testCal = DoLah::Calendar();

			for (int i = 0; i < testVector.size(); i++) {
				testCal.addTask(testVector[i]);
			}
		}

		TEST_METHOD(AddTask) {
			for (int i = 0; i < testVector.size(); i++) {
				Assert::AreEqual(testVector[i]->getName(), testCal.getTaskList()[i]->getName());
			}
		}

	};
}
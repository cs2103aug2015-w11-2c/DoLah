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
		DoLah::Calendar testCal;
		std::vector<DoLah::AbstractTask*> testVector;

	public:
		TEST_METHOD_INITIALIZE(Startup) {
			DoLah::FloatingTask* task1 = new DoLah::FloatingTask;
			task1->setName("CS2103 homework");
			task1->setDescription("draft v0.1");
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

		TEST_METHOD(EditWithNullTask) {
			DoLah::FloatingTask* nullTask = new DoLah::FloatingTask;

			testCal.updateTask(0, nullTask);

			Assert::AreEqual(testVector[0]->getName(), testCal.getTaskList()[0]->getName());
			Assert::AreEqual(testVector[0]->getDescription(), testCal.getTaskList()[0]->getDescription());
			Assert::AreEqual(testVector[0]->isDone(), testCal.getTaskList()[0]->isDone());
		}

		TEST_METHOD(EditTaskName) {
			DoLah::FloatingTask* newTask = new DoLah::FloatingTask;
			newTask->setName("go running");

			testCal.updateTask(0, newTask);

			newTask->setDescription("draft v0.1");

			Assert::AreEqual(newTask->getName(), testCal.getTaskList()[0]->getName());
			Assert::AreEqual(newTask->getDescription(), testCal.getTaskList()[0]->getDescription());
			Assert::AreEqual(newTask->isDone(), testCal.getTaskList()[0]->isDone());
		}

		TEST_METHOD(EditTaskDescription) {
			DoLah::FloatingTask* newTask = new DoLah::FloatingTask;
			newTask->setDescription("finish v0.1.1");

			testCal.updateTask(0, newTask);

			newTask->setName("CS2103 homework");

			Assert::AreEqual(newTask->getName(), testCal.getTaskList()[0]->getName());
			Assert::AreEqual(newTask->getDescription(), testCal.getTaskList()[0]->getDescription());
			Assert::AreEqual(newTask->isDone(), testCal.getTaskList()[0]->isDone());
		}

		TEST_METHOD(EditTaskStatus) {
			DoLah::FloatingTask* newTask = new DoLah::FloatingTask;
			newTask->setName("CS2103 homework");
			newTask->setDescription("draft v0.1");
			newTask->setDone(true);

			testCal.updateTask(0, newTask);

			Assert::AreEqual(newTask->getName(), testCal.getTaskList()[0]->getName());
			Assert::AreEqual(newTask->getDescription(), testCal.getTaskList()[0]->getDescription());
			Assert::AreEqual(newTask->isDone(), testCal.getTaskList()[0]->isDone());
		}
	};

	TEST_CLASS(COMMAND_TESTER) {
	private:
		DoLah::Calendar testCal = DoLah::Calendar();
		std::vector<DoLah::AbstractTask*> testVector;
	
	public:
		TEST_METHOD(AddCommand) {
			DoLah::FloatingTask* task = new DoLah::FloatingTask;
			task->setName("CS2103 homework");
			task->setDescription("draft v0.1");
			testVector.push_back(task);

			DoLah::AddTaskCommand adder = DoLah::AddTaskCommand(task);
			adder.setCalendar(&testCal);
			adder.execute();

			for (int i = 0; i < testVector.size(); i++) {
				Assert::AreEqual(testVector[i]->getName(), testCal.getTaskList()[i]->getName());
			}
		}
	};
}
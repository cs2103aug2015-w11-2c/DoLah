#include "stdafx.h"
#include "CppUnitTest.h"

#include "Models/Task.h"
#include "Commands/Command.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest
{		

	TEST_CLASS(COMMAND_TESTER) {
	public:

		TEST_METHOD(TestTask) {
			DoLah::AbstractTask* task = dynamic_cast<DoLah::AbstractTask*>(&DeadlineTask()); 
			DoLah::AddTaskCommand addCmd = DoLah::AddTaskCommand();

			task->setName("myeaow");
			addCmd.setNewTask(task);

			Assert::AreEqual(task->getName(), addCmd.getNewTask()->getName());
		}

	};
}
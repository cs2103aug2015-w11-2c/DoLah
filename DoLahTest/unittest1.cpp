#include "stdafx.h"
#include "CppUnitTest.h"

#include "basic.h"

#include "..\DoLah\Models\Task.h"
#include "..\DoLah\Commands\Command.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest
{		
	TEST_CLASS(UnitTest1){
	public:
		
		TEST_METHOD(TestMethod1)
		{
            int result = add(1, 1);
            Assert::AreEqual(result, 2);
		}

	};

	TEST_CLASS(COMMAND_TESTER) {
	public:

		TEST_METHOD(TestTask) {
			DoLah::AbstractTask* task = dynamic_cast<DoLah::AbstractTask*>(&DeadlineTask()); 
			//DoLah::AbstractTask* task1 = dynamic_cast<DoLah::AbstractTask*>(&DeadlineTask());
			DoLah::AddTaskCommand addCmd = DoLah::AddTaskCommand();

			task->setName("myeaow");
			addCmd.setTask(task);

			Assert::AreEqual(task->getName(), addCmd.getTask()->getName());
			//Assert::AreSame(task, addCmd.getTask());
		}

	};
}
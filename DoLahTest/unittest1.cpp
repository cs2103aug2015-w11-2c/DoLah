#include "stdafx.h"
#include "CppUnitTest.h"

#include "basic.h"

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

	}
}
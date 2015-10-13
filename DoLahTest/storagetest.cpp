#include "stdafx.h"
#include "CppUnitTest.h"

#include "Models/Task.h"
#include "Commands/Command.h"

#include "DoLahClient.h"
#include "Storage/CalendarStorage.h"

#include "CalendarBuilder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest
{

    TEST_CLASS(Storage) {
    public:

        TEST_METHOD(TestSaveCalendar) {
            DoLah::Calendar calendar = CalendarBuilder::buildSimpleCalendar();
            Assert::AreEqual(std::to_string(calendar.getTaskList().size()), std::string("15"));
            DoLah::CalendarStorage::save(calendar);
        }

    };
}
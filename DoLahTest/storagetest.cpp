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
            // Arrange
            DoLah::Calendar calendar = CalendarBuilder::buildSimpleCalendar();
            assert(calendar.getTaskList().size() != 0);

            // Act
            DoLah::CalendarStorage::save(calendar);

            // Assert
            YAML::Node calNode = YAML::LoadFile("calendar.yaml");
            Assert::IsTrue(calNode.IsMap());
            Assert::IsTrue(calNode["todo"].IsSequence());
            Assert::IsTrue(calNode["todo"][0].IsMap());
            Assert::AreEqual(
                std::string(calendar.getTaskList()[0]->getName()),
                calNode["todo"][0]["task"].as<std::string>());
            Assert::AreEqual(
                std::string(calendar.getTaskList()[0]->getDescription()),
                calNode["todo"][0]["description"].as<std::string>());
            Assert::AreEqual(calendar.getTaskList().size(), calNode["todo"].size() + calNode["done"].size());
        }


        TEST_METHOD(TestLoadCalendar) {
            // Arrange
            DoLah::Calendar calendar;

            // Act
            DoLah::CalendarStorage::load(calendar);

            // Assert
            YAML::Node calNode = YAML::LoadFile("calendar.yaml");
            Assert::AreEqual(
                std::string(calendar.getTaskList()[0]->getName()),
                calNode["todo"][0]["task"].as<std::string>());
            Assert::AreEqual(
                std::string(calendar.getTaskList()[0]->getDescription()),
                calNode["todo"][0]["description"].as<std::string>());
            Assert::AreEqual(calendar.getTaskList().size(), calNode["todo"].size() + calNode["done"].size());
        }
    };
}
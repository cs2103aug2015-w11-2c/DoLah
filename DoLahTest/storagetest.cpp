//@@collate A0116631M
#include "stdafx.h"
#include "CppUnitTest.h"

#include "Models/Task.h"
#include "Commands/Command.h"

#include "DoLahClient.h"
#include "Storage/CalendarStorage.h"

#include "CalendarBuilder.h"
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest
{
    const char* TEST_FIXTURE_FILENAME = "test_calendar.yaml";
    const std::string SAMPLE_FIXTURE_COMPLEX_CONTENT = R"(---
todo:  # Todo Tasks
    - task: Floating Task 0
      description: A task description for floating task 0
    - task: Deadline Task 2
      due: 2016-08-16 03:10:15
      description: A task description for deadline task 2
    - description: A task description for event task 4
      end: 2015-10-18 00:10:15
      start: 2015-10-16 23:10:15
      task: Event Task 4
done:  # Completed Tasks
    - start: 2015-10-16 23:10:15
      end: 2015-10-18 00:10:15
      task: Event Task 1
      description: A task description for event task 1
    - task: Floating Task 3
      description: A task description for floating task 3
    - task: Deadline Task 5
      due: 2016-08-16 03:10:15
      description: A task description for deadline task 5
...)";
    const std::string SAMPLE_FIXTURE_SIMPLE_CONTENT = R"(---
todo:  # Todo Tasks
    - description: A task description for event task 2
      end: 2015-10-18 00:10:15
      start: 2015-10-16 23:10:15
      task: Event Task 2
    - task: Deadline Task 1
      due: 2016-08-16 03:10:15
      description: A task description for deadline task 1
    - task: Floating Task 0
      description: A task description for floating task 0
...)";


    TEST_CLASS(Storage) {
    public:
        TEST_METHOD_INITIALIZE(Setup) {
            std::remove(TEST_FIXTURE_FILENAME);
        }

        TEST_METHOD_CLEANUP(Teardown)
        {
            std::remove(TEST_FIXTURE_FILENAME);
        }

        TEST_METHOD(TestSaveCalendar) {
            // Arrange
            DoLah::Calendar calendar = CalendarBuilder::buildSimpleCalendar();
            assert(calendar.getTaskList().size() != 0);

            // Act
            DoLah::CalendarStorage::save(calendar, TEST_FIXTURE_FILENAME);

            // Assert
            YAML::Node calNode = YAML::LoadFile(TEST_FIXTURE_FILENAME);
            Assert::IsTrue(calNode.IsMap());
            Assert::IsTrue(calNode["todo"].IsSequence());
            Assert::IsTrue(calNode["todo"][0].IsMap());
            Assert::AreEqual(
                std::string(calendar.getTaskList()[0]->getName()),
                calNode["todo"][0]["task"].as<std::string>());
            Assert::AreEqual(
                std::string(calendar.getTaskList()[0]->getDescription()),
                calNode["todo"][0]["description"].as<std::string>());
            Assert::AreEqual(calNode["todo"].size() + calNode["done"].size(), calendar.getAllTaskList().size());
        }


        TEST_METHOD(TestLoadCalendarAllTask) {
            // Arrange
            // Create a temporary fixture file
            if (!std::ifstream(TEST_FIXTURE_FILENAME)) {
                std::ofstream out(TEST_FIXTURE_FILENAME);
                out << SAMPLE_FIXTURE_COMPLEX_CONTENT;
                out.close();
            }

            // Act
            // load the temporary fixture file
            DoLah::Calendar calendar = DoLah::CalendarStorage::load(TEST_FIXTURE_FILENAME);

            // Assert
            YAML::Node calNode = YAML::LoadFile(TEST_FIXTURE_FILENAME);
            Assert::AreEqual(calNode["done"].size(), calendar.getDoneList().size());
            Assert::AreEqual(calNode["todo"].size(), calendar.getTaskList().size());
        }

        TEST_METHOD(TestLoadCalendarTaskDetail) {
            // Arrange
            // Create a temporary fixture file
            if (!std::ifstream(TEST_FIXTURE_FILENAME)) {
                std::ofstream out(TEST_FIXTURE_FILENAME);
                out << SAMPLE_FIXTURE_SIMPLE_CONTENT;
                out.close();
            }

            // Act
            // load the temporary fixture file
            DoLah::Calendar calendar = DoLah::CalendarStorage::load(TEST_FIXTURE_FILENAME);

            // Assert
            YAML::Node calNode = YAML::LoadFile(TEST_FIXTURE_FILENAME);
            std::vector<DoLah::AbstractTask*> taskList = calendar.getAllTaskList();

            // Assert Task Details
            for (size_t i = 0; i < taskList.size(); ++i) {
                Assert::AreEqual(calNode["todo"][i]["task"].as<std::string>(), taskList[i]->getName());
                Assert::AreEqual(calNode["todo"][i]["description"].as<std::string>(), taskList[i]->getDescription());
            }

            // Assert Floating Task Details
            DoLah::FloatingTask* floatingTask = dynamic_cast<DoLah::FloatingTask*>(taskList[2]);
            Assert::IsNotNull(floatingTask);


            // Assert Deadline Task Details
            DoLah::DeadlineTask* deadlineTask = dynamic_cast<DoLah::DeadlineTask*>(taskList[1]);
            std::tm due = calNode["todo"][1]["due"].as<std::tm>();
            Assert::IsNotNull(deadlineTask);
            Assert::AreEqual(0.0, difftime(mktime(&due), mktime(&deadlineTask->getDueDate())));


            // Assert Event Task Details
            DoLah::EventTask* eventTask = dynamic_cast<DoLah::EventTask*>(taskList[0]);
            std::tm start = calNode["todo"][0]["start"].as<std::tm>();
            std::tm end = calNode["todo"][0]["end"].as<std::tm>();
            Assert::IsNotNull(eventTask);
            Assert::AreEqual(0.0, difftime(mktime(&start), mktime(&eventTask->getStartDate())));
            Assert::AreEqual(0.0, difftime(mktime(&end), mktime(&eventTask->getEndDate())));
        }
    };
}
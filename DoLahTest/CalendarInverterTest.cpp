//@@collate A0111275R
#include "stdafx.h"
#include "CppUnitTest.h"

#include "Models/Task.h"
#include "Models/Calendar.h"
#include "CalendarBuilder.h"
#include "TaskBuilder.h"
#include "Models/CalendarInverter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest
{
    TEST_CLASS(CALENDAR_INVERTER_TESTER) {
private:

public:
    TEST_METHOD(UndoAddTask) {
        //Arrange
        DoLah::Calendar testCal = DoLah::Calendar();
        DoLah::FloatingTask* task = TaskBuilder::buildFloatingTask();
        testCal.addTask(task);

        //Act
        DoLah::CalendarInverter::invertAdd(task, &testCal);

        //Assert
        Assert::IsTrue(testCal.getTaskList().empty());
    }

    TEST_METHOD(UndoDeleteTask) {
        //Arrange
        DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
        int oldLength = testCal.getTaskList().size();
        DoLah::AbstractTask * task = testCal.getTask(oldLength-1);
        testCal.deleteTask(oldLength-1);

        //Act
        DoLah::CalendarInverter::invertDelete(task, &testCal);

        //Assert
        Assert::AreEqual((size_t)oldLength, testCal.getTaskList().size());
        Assert::AreEqual(task->getName(), testCal.getTaskList()[oldLength-1]->getName());
        Assert::AreEqual(task->getDescription(), testCal.getTaskList()[oldLength-1]->getDescription());
        Assert::AreEqual(task->isDone(), testCal.getTaskList()[oldLength-1]->isDone());
    }

    TEST_METHOD(UndoSetDoneTask) {
        // Arrange
        DoLah::Calendar cal = DoLah::Calendar();
        DoLah::AbstractTask * task = TaskBuilder::buildFloatingTask();
        task->setDone(false);
        cal.addTask(task);
        assert(cal.getTask(0)->isDone() == false);
        cal.setDoneTask(0);

        // Act
        DoLah::CalendarInverter::invertDone(task, &cal);

        // Assert
        Assert::IsFalse(cal.getTask(0)->isDone());
        Assert::IsFalse(cal.getTaskList().empty());
        Assert::IsTrue(cal.getDoneList().empty());
    }

    TEST_METHOD(UndoSetUnDoneTask) {
        // Arrange
        DoLah::Calendar cal = DoLah::Calendar();
        DoLah::AbstractTask * task = TaskBuilder::buildFloatingTask();
        task->setDone(true);
        cal.addTask(task);
        assert(cal.getDone(0)->isDone() == true);
        cal.setDoneTask(0, false);

        // Act
        DoLah::CalendarInverter::invertDone(task, &cal);

        // Assert
        Assert::IsTrue(cal.getDone(0)->isDone());
        Assert::IsFalse(cal.getDoneList().empty());
        Assert::IsTrue(cal.getTaskList().empty());
    }

    TEST_METHOD(UndoEditTask) {
        //Arrange
        DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
        DoLah::AbstractTask* oldTask = testCal.getTaskList()[0];
        DoLah::DeadlineTask* newTask = TaskBuilder::buildDeadlineTask();
        testCal.updateTask(0, newTask);

        //Act
        DoLah::CalendarInverter::invertEdit(oldTask, &testCal);

        //Assert
        Assert::AreEqual(oldTask->getName(), testCal.getTaskList()[0]->getName());
        Assert::AreEqual(oldTask->getDescription(), testCal.getTaskList()[0]->getDescription());
        Assert::AreEqual(oldTask->isDone(), testCal.getTaskList()[0]->isDone());
    }

    TEST_METHOD(UndoClearTask) {
        //Arrange
        DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
        std::vector<DoLah::AbstractTask*> oldTasks = testCal.getAllTaskList();
        testCal.clearTasks();

        //Act
        DoLah::CalendarInverter::invertClear(oldTasks, &testCal);

        //Assert
        Assert::IsFalse(testCal.getTaskList().empty());
    }

    };
}
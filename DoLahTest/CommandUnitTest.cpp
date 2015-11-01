#include "stdafx.h"
#include "CppUnitTest.h"

#include "Models/Task.h"
#include "Commands/Command.h"
#include "Models/Calendar.h"
#include "CalendarBuilder.h"
#include "TaskBuilder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest
{
    TEST_CLASS(COMMAND_TESTER) {
    private:
        std::string INVALID_UNDO_CALL_MESSAGE = "There is nothing to undo!";
        std::string INVALID_REDO_CALL_MESSAGE = "There is nothing to redo!";
    public:
        TEST_METHOD(AddTaskCommand) {
            //Arrange
            DoLah::Calendar testCal = DoLah::Calendar();
            DoLah::FloatingTask* task = TaskBuilder::buildFloatingTask();
            DoLah::AddTaskCommand addCommand = DoLah::AddTaskCommand(task);
            addCommand.setCalendar(&testCal);

            //Act
            addCommand.execute();

            //Assert
            Assert::AreEqual((size_t)1, testCal.getTaskList().size());
            Assert::AreEqual(task->getName(), testCal.getTaskList()[0]->getName());
            Assert::AreEqual(task->getDescription(), testCal.getTaskList()[0]->getDescription());
        }

        TEST_METHOD(DeleteTaskCommand) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
            int oldLength = testCal.getTaskList().size();
            DoLah::DeleteTaskCommand delCommand = DoLah::DeleteTaskCommand(4);
            delCommand.setCalendar(&testCal);

            //Act
            delCommand.execute();

            //Assert
            Assert::AreEqual((size_t)oldLength - 1, testCal.getTaskList().size());
        }

        TEST_METHOD(EditTaskCommand) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
            DoLah::DeadlineTask* task = TaskBuilder::buildDeadlineTask();
            DoLah::EditTaskCommand editCommand = DoLah::EditTaskCommand(0, task);
            editCommand.setCalendar(&testCal);

            //Act
            editCommand.execute();

            //Assert
            Assert::AreEqual(task->getName(), testCal.getTaskList()[task->getId()]->getName());
            Assert::AreEqual(task->getDescription(), testCal.getTaskList()[task->getId()]->getDescription());
            Assert::AreEqual(task->isDone(), testCal.getTaskList()[task->getId()]->isDone());
        }

        TEST_METHOD(ClearTaskCommand) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
            DoLah::ClearTaskCommand clearCommand = DoLah::ClearTaskCommand();
            clearCommand.setCalendar(&testCal);

            //Act
            clearCommand.execute();

            //Assert
            Assert::IsTrue(testCal.getTaskList().empty());
        }

        TEST_METHOD(SearchTaskCommand) {
            //Arrange
            DoLah::Calendar testCal = CalendarBuilder::buildSimpleCalendar();
            DoLah::SearchTaskCommand searchCommand = DoLah::SearchTaskCommand("Floating");
            searchCommand.setCalendar(&testCal);
            
            //Act
            searchCommand.execute();
            std::vector<DoLah::AbstractTask*> resultVector = testCal.getSearchedTaskList();

            //Assert
            Assert::AreEqual((size_t) 5, resultVector.size());
        }

        TEST_METHOD(UndoCommand) {
            //Arrange
            DoLah::Calendar testCal = DoLah::Calendar();
            DoLah::FloatingTask* task = TaskBuilder::buildFloatingTask();
            DoLah::AddTaskCommand addCommand = DoLah::AddTaskCommand(task);
            DoLah::UndoTaskCommand undoCommand = DoLah::UndoTaskCommand();
            addCommand.setCalendar(&testCal);
            undoCommand.setCalendar(&testCal);
            addCommand.execute();
            testCal.getCmdHistory()->addToUndoStack(&addCommand);

            //Act
            undoCommand.execute();

            //Assert
            Assert::IsTrue(testCal.getTaskList().empty());
            Assert::IsTrue(testCal.getDoneList().empty());
        }

        TEST_METHOD(InvalidUndoCommand) {
            //Arrange
            DoLah::Calendar testCal = DoLah::Calendar();
            DoLah::UndoTaskCommand undoCommand = DoLah::UndoTaskCommand();
            undoCommand.setCalendar(&testCal);

            //Act
            try {
                undoCommand.execute();
            }
            //Assert
            catch (std::out_of_range e) {
                Assert::AreEqual(INVALID_UNDO_CALL_MESSAGE, (std::string) e.what());
            }
        }

        TEST_METHOD(DoubleUndoCommand) {
            //Arrange
            DoLah::Calendar testCal = DoLah::Calendar();
            DoLah::FloatingTask* task = TaskBuilder::buildFloatingTask();
            DoLah::AddTaskCommand addCommand = DoLah::AddTaskCommand(task);
            DoLah::UndoTaskCommand undoCommand = DoLah::UndoTaskCommand();
            addCommand.setCalendar(&testCal);
            undoCommand.setCalendar(&testCal);
            addCommand.execute();
            testCal.getCmdHistory()->addToUndoStack(&addCommand);

            //Act
            try {
                undoCommand.execute();
                undoCommand.execute();
            }
            //Assert
            catch (std::out_of_range e) {
                Assert::AreEqual(INVALID_UNDO_CALL_MESSAGE, (std::string) e.what());
                Assert::IsTrue(testCal.getTaskList().empty());
                Assert::IsTrue(testCal.getDoneList().empty());
            }
        }

        TEST_METHOD(RedoAddCommand) {
            //Arrange
            DoLah::Calendar testCal = DoLah::Calendar();
            DoLah::FloatingTask* task = TaskBuilder::buildFloatingTask();
            DoLah::AddTaskCommand addCommand = DoLah::AddTaskCommand(task);
            DoLah::UndoTaskCommand undoCommand = DoLah::UndoTaskCommand();
            DoLah::RedoTaskCommand redoCommand = DoLah::RedoTaskCommand();
            addCommand.setCalendar(&testCal);
            undoCommand.setCalendar(&testCal);
            redoCommand.setCalendar(&testCal);
            addCommand.execute();
            testCal.getCmdHistory()->addToUndoStack(&addCommand);
            undoCommand.execute();

            //Act
            redoCommand.execute();

            //Assert
            Assert::AreEqual((size_t)1, testCal.getTaskList().size());
            Assert::AreEqual(task->getName(), testCal.getTaskList()[0]->getName());
            Assert::AreEqual(task->getDescription(), testCal.getTaskList()[0]->getDescription());
        }

        TEST_METHOD(InvalidRedoCommand) {
            //Arrange
            DoLah::Calendar testCal = DoLah::Calendar();
            DoLah::RedoTaskCommand redoCommand = DoLah::RedoTaskCommand();
            redoCommand.setCalendar(&testCal);

            //Act
            try {
                redoCommand.execute();
            //Assert
            } catch (std::out_of_range e) {
                Assert::AreEqual(INVALID_REDO_CALL_MESSAGE, (std::string) e.what());
            }
        }

        TEST_METHOD(DoubleUndoRedoCommand) {
            //Arrange
            DoLah::Calendar testCal = DoLah::Calendar();
            DoLah::FloatingTask* task = TaskBuilder::buildFloatingTask();
            DoLah::AddTaskCommand addCommand = DoLah::AddTaskCommand(task);
            DoLah::UndoTaskCommand undoCommand = DoLah::UndoTaskCommand(); 
            DoLah::RedoTaskCommand redoCommand = DoLah::RedoTaskCommand();
            addCommand.setCalendar(&testCal);
            undoCommand.setCalendar(&testCal);
            redoCommand.setCalendar(&testCal);
            addCommand.execute();
            testCal.getCmdHistory()->addToUndoStack(&addCommand);

            //Act
            undoCommand.execute();
            redoCommand.execute();
            undoCommand.execute();
            redoCommand.execute();

            //Assert
            Assert::AreEqual((size_t)1, testCal.getTaskList().size());
            Assert::AreEqual(task->getName(), testCal.getTaskList()[0]->getName());
            Assert::AreEqual(task->getDescription(), testCal.getTaskList()[0]->getDescription());
        }
    };
}
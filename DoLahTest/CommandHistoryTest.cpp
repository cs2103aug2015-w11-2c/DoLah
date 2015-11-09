//@@collate A0111275R
#include "stdafx.h"
#include "CppUnitTest.h"

#include "Commands/Command.h"
#include "Models/CommandHistory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest {

    TEST_CLASS(COMMAND_HISTORY_TESTER){
    private:
        std::string INVALID_UNDO_CALL_MESSAGE = "There is nothing to undo!";
        std::string INVALID_REDO_CALL_MESSAGE = "There is nothing to redo!";
    public:

        TEST_METHOD(InvalidUndo) {
            //Arrange
            DoLah::CommandHistory testCommHist = DoLah::CommandHistory();

            //Act
            try {
                testCommHist.undo();
            //Assert
            }
            catch (std::out_of_range e) {
                Assert::AreEqual(INVALID_UNDO_CALL_MESSAGE, (std::string) e.what());
            }
        }

        TEST_METHOD(ValidUndo) {
            //Arrange
            DoLah::CommandHistory testCommHist = DoLah::CommandHistory();
            DoLah::AbstractCommand * command = new DoLah::AddTaskCommand;
            testCommHist.addToUndoStack(command);

            //Act
            testCommHist.undo();

            //Assert
            Assert::AreEqual(0, testCommHist.getUndoStackSize());
            Assert::AreEqual(1, testCommHist.getRedoStackSize());
        }

        TEST_METHOD(DoubleUndo) {
            //Arrange
            DoLah::CommandHistory testCommHist = DoLah::CommandHistory();
            DoLah::AbstractCommand * command = new DoLah::AddTaskCommand;
            testCommHist.addToUndoStack(command);
            testCommHist.addToUndoStack(command);

            //Act
            testCommHist.undo();
            testCommHist.undo();

            //Assert
            Assert::AreEqual(0, testCommHist.getUndoStackSize());
            Assert::AreEqual(2, testCommHist.getRedoStackSize());
        }

        TEST_METHOD(InvalidRedo) {
            //Arrange
            DoLah::CommandHistory testCommHist = DoLah::CommandHistory();

            //Act
            try {
                testCommHist.redo();
                //Assert
            }
            catch (std::out_of_range e) {
                Assert::AreEqual(INVALID_REDO_CALL_MESSAGE, (std::string) e.what());
            }
        }

        TEST_METHOD(ValidRedo) {
            //Arrange
            DoLah::CommandHistory testCommHist = DoLah::CommandHistory();
            DoLah::AbstractCommand * command = new DoLah::AddTaskCommand;
            testCommHist.addToUndoStack(command);
            testCommHist.undo();

            //Act
            testCommHist.redo();

            //Assert
            Assert::AreEqual(1, testCommHist.getUndoStackSize());
            Assert::AreEqual(0, testCommHist.getRedoStackSize());
        }

        TEST_METHOD(DoubleRedo) {
            //Arrange
            DoLah::CommandHistory testCommHist = DoLah::CommandHistory();
            DoLah::AbstractCommand * command = new DoLah::AddTaskCommand;
            testCommHist.addToUndoStack(command);
            testCommHist.addToUndoStack(command);
            testCommHist.undo();
            testCommHist.undo();

            //Act
            testCommHist.redo();
            testCommHist.redo();

            //Assert
            Assert::AreEqual(2, testCommHist.getUndoStackSize());
            Assert::AreEqual(0, testCommHist.getRedoStackSize());
        }

        TEST_METHOD(AlternatingUndoRedo) {
            //Arrange
            DoLah::CommandHistory testCommHist = DoLah::CommandHistory();
            DoLah::AbstractCommand * command = new DoLah::AddTaskCommand;
            testCommHist.addToUndoStack(command);

            //Act
            testCommHist.undo();
            testCommHist.redo();
            testCommHist.undo();
            testCommHist.redo();
            testCommHist.undo();

            //Assert
            Assert::AreEqual(0, testCommHist.getUndoStackSize());
            Assert::AreEqual(1, testCommHist.getRedoStackSize());
        }
    };
}
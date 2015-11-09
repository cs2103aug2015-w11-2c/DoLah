//@@author A0111275R
#pragma once

#include <stack>

namespace DoLah {
    //Class forward declared in order to use.
    class AbstractCommand;

    /**
     * @class CommandHistory CommandHistory.h Models/CommandHistory.h
     * @brief Manages the history of AbstractCommands. Belongs to a Calendar.
     * 
     * Ideally this class should be accessed as a member of Calendar or
     * CommandInvoker. This class purely stores AbstractCommands and does
     * not actually perform undo or redo actions.
     */
	class CommandHistory {

	public:
        CommandHistory();
		~CommandHistory();
        
        /**
         * @brief Returns the size of the undoStack.
         *
         * @return The size of the undoStack.
         */
        int getUndoStackSize() const;

        /**
         * @brief Returns the size of the redoStack.
         *
         * @return The size of the redoStack.
         */
        int getRedoStackSize() const;

        /**
         * @brief Adds the given command to the #undoStack
         *
         * @param command The command to be added.
         */
        void addToUndoStack(AbstractCommand *);

        /**
         * @brief Pops the last executed AbstractCommand and pushes it onto
         * the #redoStack.
         *
         * @return The last executed AbstractCommand.
         */
        AbstractCommand * undo();

        /**
        * @brief Pops the last undone AbstractCommand and pushes it onto
        * the #undoStack.
        *
        * @return The last undone AbstractCommand.
        */
        AbstractCommand * redo();

	private:
        //actual data
		std::stack<AbstractCommand *> undoStack; ///< The stack holding the list of executed Commands.
		std::stack<AbstractCommand *> redoStack; ///< The stack holding the list of undone Commands.

        //error messages
        static std::string INVALID_UNDO_CALL_MESSAGE; ///< Thrown if #undoStack is empty.
        static std::string INVALID_REDO_CALL_MESSAGE; ///< Thrown if #redoStack is empty.
	};
}
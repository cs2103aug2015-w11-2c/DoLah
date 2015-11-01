#pragma once

#include <stack>

namespace DoLah {
    class AbstractCommand;

	class CommandHistory {

	public:
        CommandHistory();
		~CommandHistory();

        void addToUndoStack(AbstractCommand *);

        AbstractCommand * undo();
        AbstractCommand * redo();

	private:
        //actual data
		std::stack<AbstractCommand *> undoStack;
		std::stack<AbstractCommand *> redoStack;

        //error messages
        static std::string INVALID_UNDO_CALL_MESSAGE;
        static std::string INVALID_REDO_CALL_MESSAGE;
	};
}
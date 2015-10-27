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
		//placeholder
		std::stack<AbstractCommand *> undoStack;
		std::stack<AbstractCommand *> redoStack;
	};
}
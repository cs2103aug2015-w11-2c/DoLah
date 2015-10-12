#pragma once

#include <stack>

namespace DoLah {
	class CommandHistory {
	public:
        CommandHistory();
		~CommandHistory();

		void redo();
		void undo();

	private:
		//placeholder
		std::stack<std::string> undoStack;
		std::stack<std::string> redoStack;
	};
}
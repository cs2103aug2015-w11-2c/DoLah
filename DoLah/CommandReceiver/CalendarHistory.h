#pragma once

#include <stack>

namespace DoLah {
	class CalendarHistory {
	public:
		CalendarHistory();
		~CalendarHistory();

		void redo();
		void undo();

	private:
		//placeholder
		std::stack<std::string> undoStack;
		std::stack<std::string> redoStack;
	};
}
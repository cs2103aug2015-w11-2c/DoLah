#pragma once

#include <stack>
#include "..\Commands\Command.h"

namespace DoLah {
	class CalendarHistory {
	public:
		CalendarHistory();
		~CalendarHistory();

		void redo();
		void undo();
		//void add(DoLah::AbstractCommand*);

	private:
		//std::stack<DoLah::AbstractCommand*> undoStack;
		//std::stack<DoLah::AbstractCommand*> redoStack;
	};
}
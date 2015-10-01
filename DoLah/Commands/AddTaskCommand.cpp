#include "Command.h"

namespace DoLah {
	//public
	
	/*AddTaskCommand::AddTaskCommand(std::vector<ITokenObject> tokenVector) {
		AddTaskCommand::tokenVector = tokenVector;
	}*/

	AddTaskCommand::AddTaskCommand() {

	}

	AddTaskCommand::~AddTaskCommand() {

	}

	AddTaskCommand::AddTaskCommand(Calendar* cal, DoLah::AbstractTask* tk) {
		task = tk;
		calendar = cal;
	}

	DoLah::AbstractTask* AddTaskCommand::getTask() {
		return task;
	}

	void AddTaskCommand::setTask(DoLah::AbstractTask* tk) {
		task = tk;
	}

	void AddTaskCommand::execute() {

	}

	//protected
}
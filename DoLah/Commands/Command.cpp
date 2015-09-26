#include "Command.h"

DoLah::ITaskCommand::ITaskCommand(std::vector<ITokenObject> tokenVector){
	ITaskCommand::tokenVector = tokenVector;
}

#pragma once

#include <vector>
#include <stack>
#include <string>
#include <fstream>
#include "Models\Task.h"
#include "Commands\Command.h"

namespace DoLah {

	class DoLahClient {
	public:
		DoLahClient();

		void parseAndProcessCommand(std::string line);

	private:
	};
}

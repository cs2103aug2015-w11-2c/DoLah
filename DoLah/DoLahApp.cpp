#include "DoLahApp.h"

DoLahApp::DoLahApp() {}

DoLahApp::~DoLahApp() {}

void DoLahApp::start(std::string userinput) {
	dolah = DoLah(userinput);
}

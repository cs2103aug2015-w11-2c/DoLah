#include "UIDoLahWindow.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	DoLahUI::UIDoLahWindow form;
	Application::Run(%form);
}
#pragma once
#include "..\DoLah\DoLahApp.h"

namespace DoLahUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for UIDoLahWindow
	/// </summary>
	public ref class UIDoLahWindow : public System::Windows::Forms::Form
	{
	public:
		UIDoLahWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UIDoLahWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  displayarea;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->displayarea = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// displayarea
			// 
			this->displayarea->Location = System::Drawing::Point(3, 9);
			this->displayarea->Name = L"displayarea";
			this->displayarea->Size = System::Drawing::Size(278, 326);
			this->displayarea->TabIndex = 0;
			this->displayarea->Text = L"label1";
			this->displayarea->Click += gcnew System::EventHandler(this, &UIDoLahWindow::displayarea_Click);
			// 
			// UIDoLahWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 374);
			this->Controls->Add(this->displayarea);
			this->Name = L"UIDoLahWindow";
			this->Text = L"DoLah";
			this->Load += gcnew System::EventHandler(this, &UIDoLahWindow::UIDoLahWindow_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void UIDoLahWindow_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void displayarea_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	};
}

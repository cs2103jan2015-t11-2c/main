#include <iostream>
#include "UserInterface.h"

#pragma once

namespace GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ListfulGUI
	/// </summary>
	public ref class ListfulGUI : public System::Windows::Forms::Form
	{
	public:
		ListfulGUI(void)
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
		~ListfulGUI() {
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::RichTextBox^  inputTextBox;
	private: System::Windows::Forms::RichTextBox^  feedbackbox;


	private: System::Windows::Forms::Label^  welcomeMessage;
	private: System::Windows::Forms::Label^  menuList;
	private: System::Windows::Forms::PictureBox^  pictureBox1;

	private: System::Windows::Forms::Label^  quote;




	protected: 

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
		void InitializeComponent(void) {
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ListfulGUI::typeid));
			this->inputTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->feedbackbox = (gcnew System::Windows::Forms::RichTextBox());
			this->welcomeMessage = (gcnew System::Windows::Forms::Label());
			this->menuList = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->quote = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// inputTextBox
			// 
			this->inputTextBox->Location = System::Drawing::Point(88, 420);
			this->inputTextBox->Name = L"inputTextBox";
			this->inputTextBox->Size = System::Drawing::Size(299, 35);
			this->inputTextBox->TabIndex = 1;
			this->inputTextBox->Text = L"";
			this->inputTextBox->TextChanged += gcnew System::EventHandler(this, &ListfulGUI::inputTextBox_TextChanged);
			this->inputTextBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &ListfulGUI::inputTextBox_KeyDown);
			// 
			// feedbackbox
			// 
			this->feedbackbox->Location = System::Drawing::Point(88, 202);
			this->feedbackbox->Name = L"feedbackbox";
			this->feedbackbox->Size = System::Drawing::Size(299, 200);
			this->feedbackbox->TabIndex = 2;
			this->feedbackbox->Text = L"";
			this->feedbackbox->TextChanged += gcnew System::EventHandler(this, &ListfulGUI::feedbackbox_TextChanged);
			// 
			// welcomeMessage
			// 
			this->welcomeMessage->AutoSize = true;
			this->welcomeMessage->Font = (gcnew System::Drawing::Font(L"Buxton Sketch", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->welcomeMessage->ForeColor = System::Drawing::Color::BlueViolet;
			this->welcomeMessage->Location = System::Drawing::Point(154, 86);
			this->welcomeMessage->Name = L"welcomeMessage";
			this->welcomeMessage->Size = System::Drawing::Size(175, 29);
			this->welcomeMessage->TabIndex = 4;
			this->welcomeMessage->Text = L"Welcome to Listful";
			this->welcomeMessage->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// menuList
			// 
			this->menuList->AutoSize = true;
			this->menuList->Font = (gcnew System::Drawing::Font(L"Buxton Sketch", 13, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->menuList->ForeColor = System::Drawing::Color::DarkMagenta;
			this->menuList->Location = System::Drawing::Point(437, 164);
			this->menuList->Name = L"menuList";
			this->menuList->Size = System::Drawing::Size(97, 176);
			this->menuList->TabIndex = 5;
			this->menuList->Text = L"Menu Choices\r\n1) Add\r\n2) Display\r\n3) Delete\r\n4) Edit\r\n5) Search\r\n6) Clear\r\n7) Exi" 
				L"t\r\n";
			this->menuList->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(-24, -11);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(697, 519);
			this->pictureBox1->TabIndex = 6;
			this->pictureBox1->TabStop = false;
			// 
			// quote
			// 
			this->quote->AutoSize = true;
			this->quote->Font = (gcnew System::Drawing::Font(L"Buxton Sketch", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->quote->ForeColor = System::Drawing::Color::OrangeRed;
			this->quote->Location = System::Drawing::Point(95, 140);
			this->quote->Name = L"quote";
			this->quote->Size = System::Drawing::Size(0, 23);
			this->quote->TabIndex = 8;
			this->quote->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// ListfulGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(672, 509);
			this->Controls->Add(this->quote);
			this->Controls->Add(this->menuList);
			this->Controls->Add(this->welcomeMessage);
			this->Controls->Add(this->feedbackbox);
			this->Controls->Add(this->inputTextBox);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"ListfulGUI";
			this->Text = L"ListfulGUI";
			this->Load += gcnew System::EventHandler(this, &ListfulGUI::ListfulGUI_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		//
		// function: press enter to take in string
		//
	private: System::Void inputTextBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^ keypressed) {
				 if(keypressed->KeyCode==Keys::Enter){
					 //1. change to std string
					 //2. create new obj
					 //3. pass in
					 //4. take return result
					 //5. convert to system string
					 //6. diplay
					 char Buffer[999];
					 sprintf(Buffer,"%s", inputTextBox->Text);
					 std::string inputLine(Buffer);

					 UserInterface kangSing;

					 kangSing.runProgram(inputLine);
					 std::string resultInput = kangSing.runProgram(inputLine);
					 String^ feedbacktodisplay = gcnew String(resultInput.c_str());
					 feedbackbox->Text += feedbacktodisplay;

					 inputTextBox->Clear();
					 
				 }
			 }
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }

	private: System::Void feedbackbox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void inputTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
					
		 }
private: System::Void ListfulGUI_Load(System::Object^  sender, System::EventArgs^  e) {
					 UserInterface interface;		 
					 std::string resultQuote = interface.qotd();
					 String^ feedbacktoQuote = gcnew String(resultQuote.c_str());
					 quote->Text = feedbacktoQuote;
					 MessageBox::Show(feedbacktoQuote);
		 }
};
}

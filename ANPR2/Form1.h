#pragma once
#include <opencv\cv.h>
#include <opencv\ml.h>
#include <opencv\highgui.h>
#include <opencv\cxcore.h>
#include <stdio.h>
#include "Main.h"
#include "AboutmeForm.h"


namespace ANPR2 {

	using namespace System;
	using namespace System::IO;
	using namespace System::Runtime::InteropServices;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
		/************************************************************************/
		/*                          Ảnh gốc                                     */
		/************************************************************************/
	private: IplImage *src;

	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
			if (src)
			{
				IplImage *temp = src;
				cvReleaseImage(&temp);
				src = NULL;
			}
		}
		/// <summary>
		/// Required designer variable.
		/// </summary>
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  mởẢnhToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  lưuẢnhToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  thoátToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  thôngTinToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  tácGiảToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  trangChủToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  nhậnDạngToolStripMenuItem;

	private: System::Windows::Forms::PictureBox^  Source_Image_PictureBox;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  Recognise;
	private: System::Windows::Forms::Button^  Exit;
	private: System::Windows::Forms::Button^  Open_Img;
	private: System::Windows::Forms::Button^  Close_Img;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  lblDuongdan;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  Height_Label;
	private: System::Windows::Forms::Label^  Width_Label;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::CheckBox^  checkBox1;


	private: System::Windows::Forms::PictureBox^  Plate_PictureBox;
	private: System::Windows::Forms::PictureBox^  Gray_Img_pictureBox;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;

			 System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
				 this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->mởẢnhToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->nhậnDạngToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->lưuẢnhToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->thoátToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->thôngTinToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->tácGiảToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->trangChủToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->Plate_PictureBox = (gcnew System::Windows::Forms::PictureBox());
				 this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->Height_Label = (gcnew System::Windows::Forms::Label());
				 this->Width_Label = (gcnew System::Windows::Forms::Label());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				 this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
				 this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
				 this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
				 this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
				 this->Recognise = (gcnew System::Windows::Forms::Button());
				 this->Exit = (gcnew System::Windows::Forms::Button());
				 this->Open_Img = (gcnew System::Windows::Forms::Button());
				 this->Close_Img = (gcnew System::Windows::Forms::Button());
				 this->button1 = (gcnew System::Windows::Forms::Button());
				 this->Gray_Img_pictureBox = (gcnew System::Windows::Forms::PictureBox());
				 this->lblDuongdan = (gcnew System::Windows::Forms::Label());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->Source_Image_PictureBox = (gcnew System::Windows::Forms::PictureBox());
				 this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
				 this->label4 = (gcnew System::Windows::Forms::Label());
				 this->label5 = (gcnew System::Windows::Forms::Label());
				 this->label6 = (gcnew System::Windows::Forms::Label());
				 this->label7 = (gcnew System::Windows::Forms::Label());
				 this->label8 = (gcnew System::Windows::Forms::Label());
				 this->menuStrip1->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Plate_PictureBox))->BeginInit();
				 this->groupBox3->SuspendLayout();
				 this->groupBox1->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Gray_Img_pictureBox))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Source_Image_PictureBox))->BeginInit();
				 this->groupBox2->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // menuStrip1
				 // 
				 this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->fileToolStripMenuItem, 
					 this->thôngTinToolStripMenuItem});
				 this->menuStrip1->Location = System::Drawing::Point(0, 0);
				 this->menuStrip1->Name = L"menuStrip1";
				 this->menuStrip1->Size = System::Drawing::Size(809, 24);
				 this->menuStrip1->TabIndex = 10;
				 this->menuStrip1->Text = L"menuStrip1";
				 // 
				 // fileToolStripMenuItem
				 // 
				 this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->mởẢnhToolStripMenuItem, 
					 this->nhậnDạngToolStripMenuItem, this->lưuẢnhToolStripMenuItem, this->thoátToolStripMenuItem});
				 this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
				 this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
				 this->fileToolStripMenuItem->Text = L"File";
				 // 
				 // mởẢnhToolStripMenuItem
				 // 
				 this->mởẢnhToolStripMenuItem->Name = L"mởẢnhToolStripMenuItem";
				 this->mởẢnhToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
				 this->mởẢnhToolStripMenuItem->Size = System::Drawing::Size(200, 22);
				 this->mởẢnhToolStripMenuItem->Text = L"Mở ảnh              ";
				 this->mởẢnhToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::mởẢnhToolStripMenuItem_Click);
				 // 
				 // nhậnDạngToolStripMenuItem
				 // 
				 this->nhậnDạngToolStripMenuItem->Name = L"nhậnDạngToolStripMenuItem";
				 this->nhậnDạngToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::R));
				 this->nhậnDạngToolStripMenuItem->Size = System::Drawing::Size(200, 22);
				 this->nhậnDạngToolStripMenuItem->Text = L"Nhận dạng   ";
				 this->nhậnDạngToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::nhậnDạngToolStripMenuItem_Click);
				 // 
				 // lưuẢnhToolStripMenuItem
				 // 
				 this->lưuẢnhToolStripMenuItem->Name = L"lưuẢnhToolStripMenuItem";
				 this->lưuẢnhToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::X));
				 this->lưuẢnhToolStripMenuItem->Size = System::Drawing::Size(200, 22);
				 this->lưuẢnhToolStripMenuItem->Text = L"Đóng ảnh";
				 this->lưuẢnhToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::đóngẢnhToolStripMenuItem_Click);
				 // 
				 // thoátToolStripMenuItem
				 // 
				 this->thoátToolStripMenuItem->Name = L"thoátToolStripMenuItem";
				 this->thoátToolStripMenuItem->ShortcutKeys = System::Windows::Forms::Keys::F4;
				 this->thoátToolStripMenuItem->ShowShortcutKeys = false;
				 this->thoátToolStripMenuItem->Size = System::Drawing::Size(200, 22);
				 this->thoátToolStripMenuItem->Text = L"Thoát  ";
				 this->thoátToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::thoátToolStripMenuItem_Click);
				 // 
				 // thôngTinToolStripMenuItem
				 // 
				 this->thôngTinToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->tácGiảToolStripMenuItem, 
					 this->trangChủToolStripMenuItem});
				 this->thôngTinToolStripMenuItem->Name = L"thôngTinToolStripMenuItem";
				 this->thôngTinToolStripMenuItem->Size = System::Drawing::Size(71, 20);
				 this->thôngTinToolStripMenuItem->Text = L"Thông tin";
				 // 
				 // tácGiảToolStripMenuItem
				 // 
				 this->tácGiảToolStripMenuItem->Name = L"tácGiảToolStripMenuItem";
				 this->tácGiảToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::K));
				 this->tácGiảToolStripMenuItem->Size = System::Drawing::Size(198, 22);
				 this->tácGiảToolStripMenuItem->Text = L"Tác giả               ";
				 this->tácGiảToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::tácGiảToolStripMenuItem_Click);
				 // 
				 // trangChủToolStripMenuItem
				 // 
				 this->trangChủToolStripMenuItem->Name = L"trangChủToolStripMenuItem";
				 this->trangChủToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::H));
				 this->trangChủToolStripMenuItem->Size = System::Drawing::Size(198, 22);
				 this->trangChủToolStripMenuItem->Text = L"Trang chủ";
				 this->trangChủToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::trangChủToolStripMenuItem_Click);
				 // 
				 // Plate_PictureBox
				 // 
				 this->Plate_PictureBox->Location = System::Drawing::Point(278, 540);
				 this->Plate_PictureBox->Name = L"Plate_PictureBox";
				 this->Plate_PictureBox->Size = System::Drawing::Size(151, 34);
				 this->Plate_PictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
				 this->Plate_PictureBox->TabIndex = 16;
				 this->Plate_PictureBox->TabStop = false;
				 // 
				 // groupBox3
				 // 
				 this->groupBox3->Controls->Add(this->label1);
				 this->groupBox3->Controls->Add(this->Height_Label);
				 this->groupBox3->Controls->Add(this->Width_Label);
				 this->groupBox3->Controls->Add(this->label2);
				 this->groupBox3->Location = System::Drawing::Point(12, 35);
				 this->groupBox3->Name = L"groupBox3";
				 this->groupBox3->Size = System::Drawing::Size(240, 84);
				 this->groupBox3->TabIndex = 15;
				 this->groupBox3->TabStop = false;
				 this->groupBox3->Text = L"Chi tiết ảnh gốc";
				 // 
				 // label1
				 // 
				 this->label1->AccessibleRole = System::Windows::Forms::AccessibleRole::Alert;
				 this->label1->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->label1->AutoSize = true;
				 this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(163)));
				 this->label1->Location = System::Drawing::Point(16, 17);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(39, 16);
				 this->label1->TabIndex = 8;
				 this->label1->Text = L"Cao: ";
				 // 
				 // Height_Label
				 // 
				 this->Height_Label->AccessibleRole = System::Windows::Forms::AccessibleRole::Alert;
				 this->Height_Label->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->Height_Label->AutoSize = true;
				 this->Height_Label->BackColor = System::Drawing::SystemColors::Control;
				 this->Height_Label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(163)));
				 this->Height_Label->Location = System::Drawing::Point(137, 17);
				 this->Height_Label->Name = L"Height_Label";
				 this->Height_Label->Size = System::Drawing::Size(17, 16);
				 this->Height_Label->TabIndex = 10;
				 this->Height_Label->Text = L"...";
				 // 
				 // Width_Label
				 // 
				 this->Width_Label->AccessibleRole = System::Windows::Forms::AccessibleRole::Alert;
				 this->Width_Label->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->Width_Label->AutoSize = true;
				 this->Width_Label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(163)));
				 this->Width_Label->Location = System::Drawing::Point(137, 53);
				 this->Width_Label->Name = L"Width_Label";
				 this->Width_Label->Size = System::Drawing::Size(17, 16);
				 this->Width_Label->TabIndex = 11;
				 this->Width_Label->Text = L"...";
				 // 
				 // label2
				 // 
				 this->label2->AccessibleRole = System::Windows::Forms::AccessibleRole::Alert;
				 this->label2->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->label2->AutoSize = true;
				 this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(163)));
				 this->label2->Location = System::Drawing::Point(16, 53);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(47, 16);
				 this->label2->TabIndex = 9;
				 this->label2->Text = L"Rộng: ";
				 // 
				 // groupBox1
				 // 
				 this->groupBox1->Controls->Add(this->radioButton3);
				 this->groupBox1->Controls->Add(this->radioButton2);
				 this->groupBox1->Controls->Add(this->radioButton1);
				 this->groupBox1->Controls->Add(this->checkBox1);
				 this->groupBox1->Controls->Add(this->Recognise);
				 this->groupBox1->Controls->Add(this->Exit);
				 this->groupBox1->Controls->Add(this->Open_Img);
				 this->groupBox1->Controls->Add(this->Close_Img);
				 this->groupBox1->Location = System::Drawing::Point(15, 214);
				 this->groupBox1->Name = L"groupBox1";
				 this->groupBox1->Size = System::Drawing::Size(237, 252);
				 this->groupBox1->TabIndex = 14;
				 this->groupBox1->TabStop = false;
				 this->groupBox1->Text = L"Chức năng";
				 // 
				 // radioButton3
				 // 
				 this->radioButton3->AutoSize = true;
				 this->radioButton3->Checked = true;
				 this->radioButton3->Location = System::Drawing::Point(11, 134);
				 this->radioButton3->Name = L"radioButton3";
				 this->radioButton3->Size = System::Drawing::Size(79, 17);
				 this->radioButton3->TabIndex = 23;
				 this->radioButton3->TabStop = true;
				 this->radioButton3->Text = L"Không hiện";
				 this->radioButton3->UseVisualStyleBackColor = true;
				 this->radioButton3->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton3_CheckedChanged);
				 // 
				 // radioButton2
				 // 
				 this->radioButton2->AutoSize = true;
				 this->radioButton2->Location = System::Drawing::Point(11, 100);
				 this->radioButton2->Name = L"radioButton2";
				 this->radioButton2->Size = System::Drawing::Size(188, 17);
				 this->radioButton2->TabIndex = 22;
				 this->radioButton2->Text = L"Hiện ảnh trong quá trình tách kí tự";
				 this->radioButton2->UseVisualStyleBackColor = true;
				 this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton2_CheckedChanged);
				 // 
				 // radioButton1
				 // 
				 this->radioButton1->AutoSize = true;
				 this->radioButton1->Location = System::Drawing::Point(11, 62);
				 this->radioButton1->Name = L"radioButton1";
				 this->radioButton1->Size = System::Drawing::Size(178, 17);
				 this->radioButton1->TabIndex = 21;
				 this->radioButton1->Text = L"Hiện ảnh trong quá trình tìm biển";
				 this->radioButton1->UseVisualStyleBackColor = true;
				 // 
				 // checkBox1
				 // 
				 this->checkBox1->AutoSize = true;
				 this->checkBox1->Location = System::Drawing::Point(11, 19);
				 this->checkBox1->Name = L"checkBox1";
				 this->checkBox1->Size = System::Drawing::Size(121, 17);
				 this->checkBox1->TabIndex = 18;
				 this->checkBox1->Text = L"Tự động nhận dạng";
				 this->checkBox1->UseVisualStyleBackColor = true;
				 this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox1_CheckedChanged);
				 // 
				 // Recognise
				 // 
				 this->Recognise->AccessibleRole = System::Windows::Forms::AccessibleRole::Alert;
				 this->Recognise->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->Recognise->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->Recognise->Location = System::Drawing::Point(104, 167);
				 this->Recognise->Name = L"Recognise";
				 this->Recognise->Size = System::Drawing::Size(75, 21);
				 this->Recognise->TabIndex = 16;
				 this->Recognise->Text = L"Nhận dạng";
				 this->Recognise->UseVisualStyleBackColor = true;
				 this->Recognise->Click += gcnew System::EventHandler(this, &Form1::Recognise_Click);
				 // 
				 // Exit
				 // 
				 this->Exit->AccessibleRole = System::Windows::Forms::AccessibleRole::Alert;
				 this->Exit->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->Exit->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->Exit->Location = System::Drawing::Point(104, 214);
				 this->Exit->Name = L"Exit";
				 this->Exit->Size = System::Drawing::Size(75, 20);
				 this->Exit->TabIndex = 17;
				 this->Exit->Text = L"Thoát";
				 this->Exit->UseVisualStyleBackColor = true;
				 this->Exit->Click += gcnew System::EventHandler(this, &Form1::Exit_Click);
				 // 
				 // Open_Img
				 // 
				 this->Open_Img->AccessibleRole = System::Windows::Forms::AccessibleRole::Alert;
				 this->Open_Img->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->Open_Img->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->Open_Img->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(163)));
				 this->Open_Img->Location = System::Drawing::Point(7, 166);
				 this->Open_Img->Name = L"Open_Img";
				 this->Open_Img->Size = System::Drawing::Size(75, 22);
				 this->Open_Img->TabIndex = 14;
				 this->Open_Img->Text = L"Mở ảnh";
				 this->Open_Img->UseVisualStyleBackColor = true;
				 this->Open_Img->Click += gcnew System::EventHandler(this, &Form1::Open_Img_Click);
				 // 
				 // Close_Img
				 // 
				 this->Close_Img->AccessibleRole = System::Windows::Forms::AccessibleRole::Alert;
				 this->Close_Img->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->Close_Img->Cursor = System::Windows::Forms::Cursors::Hand;
				 this->Close_Img->Location = System::Drawing::Point(7, 212);
				 this->Close_Img->Name = L"Close_Img";
				 this->Close_Img->Size = System::Drawing::Size(75, 22);
				 this->Close_Img->TabIndex = 15;
				 this->Close_Img->Text = L"Đóng ảnh";
				 this->Close_Img->UseVisualStyleBackColor = true;
				 this->Close_Img->Click += gcnew System::EventHandler(this, &Form1::Close_Img_Click);
				 // 
				 // button1
				 // 
				 this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->button1->ForeColor = System::Drawing::Color::Red;
				 this->button1->Location = System::Drawing::Point(723, 540);
				 this->button1->Name = L"button1";
				 this->button1->Size = System::Drawing::Size(75, 23);
				 this->button1->TabIndex = 16;
				 this->button1->Text = L">>";
				 this->button1->UseVisualStyleBackColor = true;
				 this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
				 // 
				 // Gray_Img_pictureBox
				 // 
				 this->Gray_Img_pictureBox->Location = System::Drawing::Point(824, 70);
				 this->Gray_Img_pictureBox->Name = L"Gray_Img_pictureBox";
				 this->Gray_Img_pictureBox->Size = System::Drawing::Size(520, 464);
				 this->Gray_Img_pictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
				 this->Gray_Img_pictureBox->TabIndex = 15;
				 this->Gray_Img_pictureBox->TabStop = false;
				 // 
				 // lblDuongdan
				 // 
				 this->lblDuongdan->AutoSize = true;
				 this->lblDuongdan->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(163)));
				 this->lblDuongdan->Location = System::Drawing::Point(421, 42);
				 this->lblDuongdan->Name = L"lblDuongdan";
				 this->lblDuongdan->Size = System::Drawing::Size(17, 16);
				 this->lblDuongdan->TabIndex = 14;
				 this->lblDuongdan->Text = L"...";
				 // 
				 // label3
				 // 
				 this->label3->AutoSize = true;
				 this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(163)));
				 this->label3->Location = System::Drawing::Point(296, 42);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(76, 16);
				 this->label3->TabIndex = 13;
				 this->label3->Text = L"Đường dẫn:";
				 // 
				 // Source_Image_PictureBox
				 // 
				 this->Source_Image_PictureBox->AccessibleRole = System::Windows::Forms::AccessibleRole::Alert;
				 this->Source_Image_PictureBox->Cursor = System::Windows::Forms::Cursors::Cross;
				 this->Source_Image_PictureBox->Location = System::Drawing::Point(278, 70);
				 this->Source_Image_PictureBox->Name = L"Source_Image_PictureBox";
				 this->Source_Image_PictureBox->Size = System::Drawing::Size(520, 464);
				 this->Source_Image_PictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
				 this->Source_Image_PictureBox->TabIndex = 12;
				 this->Source_Image_PictureBox->TabStop = false;
				 // 
				 // groupBox2
				 // 
				 this->groupBox2->Controls->Add(this->label4);
				 this->groupBox2->Controls->Add(this->label5);
				 this->groupBox2->Controls->Add(this->label6);
				 this->groupBox2->Controls->Add(this->label7);
				 this->groupBox2->Location = System::Drawing::Point(12, 129);
				 this->groupBox2->Name = L"groupBox2";
				 this->groupBox2->Size = System::Drawing::Size(240, 79);
				 this->groupBox2->TabIndex = 16;
				 this->groupBox2->TabStop = false;
				 this->groupBox2->Text = L"Chi tiết ảnh biển số";
				 // 
				 // label4
				 // 
				 this->label4->AccessibleRole = System::Windows::Forms::AccessibleRole::Alert;
				 this->label4->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->label4->AutoSize = true;
				 this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(163)));
				 this->label4->Location = System::Drawing::Point(16, 15);
				 this->label4->Name = L"label4";
				 this->label4->Size = System::Drawing::Size(39, 16);
				 this->label4->TabIndex = 8;
				 this->label4->Text = L"Cao: ";
				 // 
				 // label5
				 // 
				 this->label5->AccessibleRole = System::Windows::Forms::AccessibleRole::Alert;
				 this->label5->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->label5->AutoSize = true;
				 this->label5->BackColor = System::Drawing::SystemColors::Control;
				 this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(163)));
				 this->label5->Location = System::Drawing::Point(137, 15);
				 this->label5->Name = L"label5";
				 this->label5->Size = System::Drawing::Size(17, 16);
				 this->label5->TabIndex = 10;
				 this->label5->Text = L"...";
				 // 
				 // label6
				 // 
				 this->label6->AccessibleRole = System::Windows::Forms::AccessibleRole::Alert;
				 this->label6->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->label6->AutoSize = true;
				 this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(163)));
				 this->label6->Location = System::Drawing::Point(137, 51);
				 this->label6->Name = L"label6";
				 this->label6->Size = System::Drawing::Size(17, 16);
				 this->label6->TabIndex = 11;
				 this->label6->Text = L"...";
				 // 
				 // label7
				 // 
				 this->label7->AccessibleRole = System::Windows::Forms::AccessibleRole::Alert;
				 this->label7->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->label7->AutoSize = true;
				 this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(163)));
				 this->label7->Location = System::Drawing::Point(16, 51);
				 this->label7->Name = L"label7";
				 this->label7->Size = System::Drawing::Size(47, 16);
				 this->label7->TabIndex = 9;
				 this->label7->Text = L"Rộng: ";
				 // 
				 // label8
				 // 
				 this->label8->AutoSize = true;
				 this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(163)));
				 this->label8->Location = System::Drawing::Point(15, 491);
				 this->label8->Name = L"label8";
				 this->label8->Size = System::Drawing::Size(0, 31);
				 this->label8->TabIndex = 17;
				 // 
				 // Form1
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
				 this->ClientSize = System::Drawing::Size(809, 595);
				 this->Controls->Add(this->label8);
				 this->Controls->Add(this->groupBox2);
				 this->Controls->Add(this->lblDuongdan);
				 this->Controls->Add(this->Plate_PictureBox);
				 this->Controls->Add(this->button1);
				 this->Controls->Add(this->groupBox1);
				 this->Controls->Add(this->groupBox3);
				 this->Controls->Add(this->Source_Image_PictureBox);
				 this->Controls->Add(this->label3);
				 this->Controls->Add(this->Gray_Img_pictureBox);
				 this->Controls->Add(this->menuStrip1);
				 this->MainMenuStrip = this->menuStrip1;
				 this->MaximizeBox = false;
				 this->Name = L"Form1";
				 this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				 this->Text = L"Đề tài ứng dụng OpenCV vào nhận dạng biển số";
				 this->TransparencyKey = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
					 static_cast<System::Int32>(static_cast<System::Byte>(0)));
				 this->menuStrip1->ResumeLayout(false);
				 this->menuStrip1->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Plate_PictureBox))->EndInit();
				 this->groupBox3->ResumeLayout(false);
				 this->groupBox3->PerformLayout();
				 this->groupBox1->ResumeLayout(false);
				 this->groupBox1->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Gray_Img_pictureBox))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Source_Image_PictureBox))->EndInit();
				 this->groupBox2->ResumeLayout(false);
				 this->groupBox2->PerformLayout();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion

#pragma region Chức năng
			 //
			 // Convert Kiểu String sang Char* để dùng cho nút "Open Image"
			 // [Convert String to Char* to use for "Open Image" button]
	private: char* ConvertStringtoChar (System::String ^str){
				 char *str2 = (char*) (void*) Marshal::StringToHGlobalAnsi(str);
				 return str2;
			 }

	private: Bitmap^ iplImage2Bitmap(IplImage *img)
			 {

				 Bitmap ^bmp;

				 if (img->nChannels == 1)
				 {
					 bmp = gcnew Bitmap(img->width, img->height, Imaging::PixelFormat::Format8bppIndexed);

					 Imaging::ColorPalette ^plt = bmp->Palette;

					 for (int i = 0; i < 256; i++)
					 {
						 plt->Entries[i] = Color::FromArgb(i, i, i);

						 bmp->Palette = plt;
					 }
				 }
				 else
					 bmp = gcnew Bitmap(img->width, img->height, Imaging::PixelFormat::Format24bppRgb);

				 Imaging::BitmapData ^data = bmp->LockBits(Drawing::Rectangle(0, 0, bmp->Width, bmp->Height), Imaging::ImageLockMode::ReadWrite,  bmp->PixelFormat);

				 memcpy(data->Scan0.ToPointer(), img->imageData, img->imageSize);
				 bmp->UnlockBits(data);

				 return bmp;
			 }
			 //
			 // Nút OpenImage
			 // OpenImage Button
	private: System::Void Open_Img_Click(System::Object^  sender, System::EventArgs^  e) {


				 OpenFileDialog^ dlg = gcnew OpenFileDialog;	

				 dlg->Filter = L"Chọn ảnh (*.bmp; *.jpg; *.jpeg; *.png) |*.bmp;*.jpg;*.jpeg;*.png|Tất cả các định dạng file (*.*)|*.*||";
				 if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)	return;
				 src = cvLoadImage(ConvertStringtoChar(dlg->FileName), CV_LOAD_IMAGE_ANYCOLOR); 

				 Bitmap^ bmp = gcnew Bitmap (dlg->FileName);
				 Source_Image_PictureBox->Image = bmp;
				 Source_Image_PictureBox->Refresh();

				 Height_Label->Text = src->height + " pixels";
				 Width_Label->Text  = src->width  + " pixels";

				 lblDuongdan->Text = dlg->FileName;

				 /* Tự động nhận dạng sau khi mở ảnh*/
				 if (checkBox1->Checked == true)
				 {
					 Recognise_Click(sender, e);
				 }					 				 
			 }
			 /*
			 *	Đóng ảnh
			 */
	private: System::Void Close_Img_Click(System::Object^  sender, System::EventArgs^  e) {

				 delete Source_Image_PictureBox->Image;
				 Source_Image_PictureBox->Image = nullptr;

				 delete Plate_PictureBox->Image;
				 Plate_PictureBox->Image = nullptr;

				 delete Gray_Img_pictureBox->Image;
				 Gray_Img_pictureBox->Image = nullptr;

				 IplImage *temp = src;
				 cvReleaseImage(&temp);
				 src = NULL;

				 cvDestroyAllWindows();

				 Height_Label->Text = "...";
				 Width_Label->Text  = "...";
				 label5->Text = "...";
				 label6->Text = "...";
				 lblDuongdan->Text = "...";
			 }
			 // Nhận dạng
	private: System::Void Recognise_Click(System::Object^  sender, System::EventArgs^  e) {

				 LPR_Main m; 
				 System::Windows::Forms::DialogResult noImageLoaded;
				 System::Windows::Forms::DialogResult noRecognise;

				 if (!src)
				 {
					 noImageLoaded = MessageBox::Show(L"Bạn chưa đưa ảnh vào.", L"Lỗi",
						 MessageBoxButtons::OK, MessageBoxIcon::Error);
					 if(noImageLoaded ==  Windows::Forms::DialogResult::OK)
						 return;
				 }
				 else
				 {			 
					 IplImage *plate;

					 /* Tìm biển */
					 m.show_in_find_plate = radioButton1->Checked ? true : false; 
					 plate = m.Crop_Plate(src);

					 if (!plate)  // Không tìm thấy
					 {				 
						 label8->Text = "";
						 cvDestroyAllWindows();

						 delete Plate_PictureBox->Image;
						 Plate_PictureBox->Image = nullptr;

						 delete Gray_Img_pictureBox->Image;
						 Gray_Img_pictureBox->Image = nullptr;

						 noRecognise = MessageBox::Show(L"Không thể nhận dạng được biển số.\r\n\r\nHãy thử lại với 1 ảnh khác.", L"Lỗi", 
							 MessageBoxButtons::OK, MessageBoxIcon::Stop);

						 if(noImageLoaded ==  Windows::Forms::DialogResult::OK)
						 {
							 cvReleaseImage(&plate);							
							 return;
						 }
					 }
					 /* Tìm thấy -> Nhận dạng kí tự */
					 else
					 {
						 // HIện ảnh biển số và thông tin chi tiết
						 label5->Text = plate->height + " pixel";
						 label6->Text = plate->width  + " pixel";

						 Bitmap^ plate_bmp = gcnew Bitmap (iplImage2Bitmap(plate));
						 Plate_PictureBox->Image = plate_bmp;
						 Plate_PictureBox->Refresh();

						 if (radioButton3->Checked)
						 {
							 cvDestroyAllWindows();
						 }

						 // Hiện ảnh xám có vẽ biển số
						 IplImage *gray_plate = m.Crop_Plate(src, 2);
						 Bitmap^ gray_bmp = gcnew Bitmap(iplImage2Bitmap(gray_plate));
						 Gray_Img_pictureBox->Image = gray_bmp;
						 Gray_Img_pictureBox->Refresh();

						 m.show_in_recognise = radioButton2->Checked ? true : false;

						 // Nhận dạng ký tự
						 string s = m.Recognise(plate);
						 System::String^ str = gcnew System::String(s.c_str());

						 // Show ra textbox
						 if (str->Length < 7)
						 {
							 str = L"___-____";
						 }
						 else
						 {
							 str = str->Insert(3, "-");
							 if (str->Length == 9)
							 {
								 str = str->Insert(7, ".");
							 }
						 }

						 label8->Text = str;
					 }

					 cvReleaseImage(&plate);
				 }
			 }
			 // Exit 
	private: System::Void Exit_Click(System::Object^  sender, System::EventArgs^  e) {
				 System::Windows::Forms::DialogResult result;
				 result = MessageBox::Show(L"Bạn muốn thoát?", L"Thoát",
					 MessageBoxButtons::OKCancel, MessageBoxIcon::Question);
				 if (result == Windows::Forms::DialogResult::OK)
				 {
					 delete Source_Image_PictureBox->Image;
					 Source_Image_PictureBox->Image = nullptr;

					 delete Plate_PictureBox->Image;
					 Plate_PictureBox->Image = nullptr;

					 IplImage *temp = src;
					 cvReleaseImage(&temp);
					 src = NULL;
					 cvDestroyAllWindows();

					 this->Close();
				 }
			 }

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

				 if(button1->Text == ">>")
				 {
					 this->Size = System::Drawing::Size(1400, 611);
					 button1->Text = "<<";
				 }
				 else
				 {
					 this->Size = System::Drawing::Size(825, 611);
					 button1->Text = ">>";
				 }
				 this->Refresh();
			 }
	private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 if (checkBox1->Checked)
				 {
					 Recognise->Enabled = false;
				 }
				 else
					 Recognise->Enabled = true;
			 }
	private: System::Void radioButton2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 Recognise_Click(sender, e);
			 }
	private: System::Void radioButton3_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 Recognise_Click(sender, e);
			 }

			 //URL
	private: System::Void trangChủToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 System::Diagnostics::Process::Start("http://fituct.org");
			 }
			 // About me
	private: System::Void tácGiảToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 AboutmeForm f2;
				 f2.ShowDialog();
			 }	  
	private: System::Void mởẢnhToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Open_Img_Click(sender, e);				 
			 }

	private: System::Void nhậnDạngToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Recognise_Click(sender, e);
			 }
	private: System::Void đóngẢnhToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Close_Img_Click(sender, e);
			 }

	private: System::Void thoátToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Exit_Click(sender, e);
			 }
	private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e) {
				 AboutmeForm f2;
				 f2.ShowDialog();
			 }
#pragma endregion
	};
}
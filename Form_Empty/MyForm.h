#pragma once
#include <windows.h>
#include <iostream>
#include <atlstr.h>
#include "imge.h"
#include <array>

namespace Form_Empty {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using std::cin;
	using std::cout;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ readToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		
		BYTE* Buffer;
		BYTE* Raw_Intensity;
		int Width, Height;
		long Size;

	private: System::Windows::Forms::ToolStripMenuItem^ grayImageToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ kMEANSThresholdToolStripMenuItem;
	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ListBox^ listBox2;
	private: System::Windows::Forms::ListBox^ listBox3;




		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>

		void ShowIntensity(unsigned char* img, int w, int h, PictureBox^ image_field) {
			Bitmap^ surface = gcnew Bitmap(image_field->Width, image_field->Height);
			image_field->Image = surface;
			Color c;
			int temp;
			for (int row=0; row<h; row++)
				for (int column = 0; column < w; column++) {
					temp = row * Width + column;
					c = Color::FromArgb(img[temp], img[temp], img[temp]);
					surface->SetPixel(column, row, c);
				}
		}

		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->readToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->grayImageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->kMEANSThresholdToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->listBox3 = (gcnew System::Windows::Forms::ListBox());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1451, 28);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->readToolStripMenuItem,
					this->grayImageToolStripMenuItem, this->kMEANSThresholdToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(46, 24);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// readToolStripMenuItem
			// 
			this->readToolStripMenuItem->Name = L"readToolStripMenuItem";
			this->readToolStripMenuItem->Size = System::Drawing::Size(226, 26);
			this->readToolStripMenuItem->Text = L"Read Image";
			this->readToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::readToolStripMenuItem_Click);
			// 
			// grayImageToolStripMenuItem
			// 
			this->grayImageToolStripMenuItem->Name = L"grayImageToolStripMenuItem";
			this->grayImageToolStripMenuItem->Size = System::Drawing::Size(226, 26);
			this->grayImageToolStripMenuItem->Text = L"Gray Image";
			this->grayImageToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::grayImageToolStripMenuItem_Click);
			// 
			// kMEANSThresholdToolStripMenuItem
			// 
			this->kMEANSThresholdToolStripMenuItem->Name = L"kMEANSThresholdToolStripMenuItem";
			this->kMEANSThresholdToolStripMenuItem->Size = System::Drawing::Size(226, 26);
			this->kMEANSThresholdToolStripMenuItem->Text = L"K-MEANS Threshold";
			this->kMEANSThresholdToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::kMEANSThresholdToolStripMenuItem_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(12, 40);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(986, 889);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 16;
			this->listBox1->Location = System::Drawing::Point(1031, 31);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(120, 564);
			this->listBox1->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(1028, 656);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 17);
			this->label1->TabIndex = 3;
			// 
			// listBox2
			// 
			this->listBox2->FormattingEnabled = true;
			this->listBox2->ItemHeight = 16;
			this->listBox2->Location = System::Drawing::Point(1177, 31);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(120, 564);
			this->listBox2->TabIndex = 4;
			// 
			// listBox3
			// 
			this->listBox3->FormattingEnabled = true;
			this->listBox3->ItemHeight = 16;
			this->listBox3->Location = System::Drawing::Point(1190, 698);
			this->listBox3->Name = L"listBox3";
			this->listBox3->Size = System::Drawing::Size(120, 84);
			this->listBox3->TabIndex = 5;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1451, 941);
			this->Controls->Add(this->listBox3);
			this->Controls->Add(this->listBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: System::Void readToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			CString str;
			LPCTSTR input;
			if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				str = openFileDialog1->FileName;
				pictureBox1->Width = Width;
				pictureBox1->Height = Height;
				this->pictureBox1->ImageLocation = openFileDialog1->FileName;

				input = (LPCTSTR)str;
				// BMP image okumak
				Buffer = LoadBMP(Width, Height, Size, input);

				
			}
		}
		private: System::Void grayImageToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			Raw_Intensity = ConvertToIntensity(Buffer, Width, Height);
			ShowIntensity(Raw_Intensity, Width, Height, pictureBox1);
		}
		private: System::Void kMEANSThresholdToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			// Histogram grafiði çýkarýlýyor.
			int ptr = 0;
			int size = Width * Height;
			int histData[256] = { 0 };
			while (ptr < size) {
				int h = 0xFF & Raw_Intensity[ptr];
				histData[h] ++;
				ptr++;
			}

			int temp = 0;
			for (int i = 0; i < 256; i++) {
				listBox1->Items->Add(i.ToString() + ") " + histData[i].ToString());
				temp += histData[i];
			}
			label1->Text += temp.ToString();
			int k = 2;

			// k deðerlerini rastgele sayýlara eþitliyoruz.
			double* cluster_means = new double[k];
			double* cluster_temp_means = new double[k];
			int* cluster_sum = new int[k];
			double* cluster_count = new double[k];
			Random^ rand = gcnew Random;
			for (int i = 0; i < k; i++) {
				cluster_means[i] = 0;
				cluster_temp_means[i] = rand->Next(0, 255);
				cluster_sum[i] = 0;
				cluster_count[i] = 0;
				label1->Text += "  " + cluster_temp_means[i].ToString();
			}

			int count = 1;
			while (Math::Abs(cluster_means[0] - cluster_temp_means[0]) > 0.1) {
				for (int i = 0; i < k; i++) {
					cluster_means[i] = cluster_temp_means[i];
				}
				// Histogram deðerleri üzerinde küme atama iþlemi gerçekleþtirilir.
				int assigments[256] = { 0 };
				for (int point = 0; point < 256; point++) {
					double min_distance = Double::MaxValue;
					int min_cluster = 0;
					for (int cluster = 0; cluster < k; cluster++) {
						const double distance = Math::Abs(point - cluster_means[cluster]); // Fonlsiyona dönüþtürülecek
						if (distance < min_distance) {
							min_distance = distance;
							min_cluster = cluster;
						}
					}
					assigments[point] = min_cluster;
				}
			
				for (int point = 0; point < 256; point++) {
					const int cluster_no = assigments[point];
					cluster_sum[cluster_no] += histData[point] * point;
					cluster_count[cluster_no] += histData[point];
				}

				for (int i = 0; i < k; i++) {
					cluster_temp_means[i] = cluster_sum[i] / cluster_count[i];
					listBox3->Items->Add(count.ToString() + ") " + cluster_temp_means[i].ToString());
				}
				count++;
				for (int i = 0; i < 256; i++) {
					listBox2->Items->Add(i.ToString() + ") " + assigments[i].ToString());
				}
			}

			int color[2] = { 0,255 };
			for (int i = 0; i < size; i++) {
				double min_distance = Double::MaxValue;
				int min_cluster = 0;
				for (int cluster = 0; cluster < k; cluster++) {
					const double distance = Math::Abs(Raw_Intensity[i] - cluster_means[cluster]); // Fonlsiyona dönüþtürülecek
					if (distance < min_distance) {
						min_distance = distance;
						min_cluster = cluster;
					}
				}
				Raw_Intensity[i] = color[min_cluster];
			}
			ShowIntensity(Raw_Intensity, Width, Height, pictureBox1);
		}
	};
}

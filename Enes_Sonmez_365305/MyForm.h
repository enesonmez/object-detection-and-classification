#pragma once
#include <windows.h>
#include <iostream>
#include <atlstr.h>
#include <array>
#include <limits.h>
#include "imge.h"
#include "helper.h"
#include "hu_moments.h"

namespace Form_Empty {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
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
		
		BYTE* Buffer;			// RGB IMAGE VALUES
		BYTE* Raw_Intensity;	// GRAY IMAGE VALUES 
		BYTE* Binary_Image;		// BINARY IMAGE VALUES
		int Width, Height;		// IMAGE WIDTH - HEIGHT
		long Size;				// IMAGE SIZE
		unsigned int* Histogram_Values;

		DB_MOMENT* db = new DB_MOMENT[20];
		int db_moment_count = 0;
		double* moments = new double[7];

	private: System::Windows::Forms::ToolStripMenuItem^ grayImageToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ kMEANSThresholdToolStripMenuItem;
	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ListBox^ listBox2;


	private: System::Windows::Forms::ToolStripMenuItem^ histogramToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ morphologyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ erosionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ dilationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ closingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ labellingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ featureProcessToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ featureExtractionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ saveDatabaseToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ testImageToolStripMenuItem;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ histogramChart;
	private: System::Windows::Forms::ToolStripMenuItem^ invertBinaryImageToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::ToolStripMenuItem^ rGBLabellingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ objectDectectToolStripMenuItem;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::ListBox^ listBox3;
	private: System::Windows::Forms::Label^ label3;





		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		
		// Gri resmi picturebox'a yazdýrma
		void ShowIntensity(unsigned char* img, int w, int h, PictureBox^ image_field) {
			Bitmap^ surface = gcnew Bitmap(image_field->Width, image_field->Height);
			image_field->Image = surface;
			Color c;
			int temp;
			for (int row=0; row<h; row++)
				for (int column = 0; column < w; column++) {
					temp = row * w + column;
					c = Color::FromArgb(img[temp], img[temp], img[temp]);
					surface->SetPixel(column, row, c);
				}
		}
		
		// Etiketlenmiþ resimdeki nesnelerin renkli gösterimini picturebox'a bastýrma
		void ShowLabelingRGBImage(unsigned char* labeledImage, int w, int h, PictureBox^ image_field, int* colors) {
			Bitmap^ surface = gcnew Bitmap(image_field->Width, image_field->Height);
			image_field->Image = surface;
			Color c;
			int temp;
			for (int row = 0; row < h; row++)
				for (int column = 0; column < w; column++) {
					temp = row * w + column;
					int point = labeledImage[temp];
					if (point != 0) {
						int order = (point - 1) * 3;
						c = Color::FromArgb(colors[order], colors[order + 1], colors[order + 2]);
					}
					else
						c = Color::FromArgb(0, 0, 0);
					surface->SetPixel(column, row, c);
				}
		}

		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->readToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->grayImageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->histogramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->kMEANSThresholdToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->invertBinaryImageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->morphologyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->erosionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dilationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->closingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->labellingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rGBLabellingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->objectDectectToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->featureProcessToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->featureExtractionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveDatabaseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->testImageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->histogramChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->listBox3 = (gcnew System::Windows::Forms::ListBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->histogramChart))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->fileToolStripMenuItem,
					this->morphologyToolStripMenuItem, this->labellingToolStripMenuItem, this->featureProcessToolStripMenuItem, this->testImageToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(4, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(1443, 27);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->readToolStripMenuItem,
					this->grayImageToolStripMenuItem, this->histogramToolStripMenuItem, this->kMEANSThresholdToolStripMenuItem, this->invertBinaryImageToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(43, 23);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// readToolStripMenuItem
			// 
			this->readToolStripMenuItem->Name = L"readToolStripMenuItem";
			this->readToolStripMenuItem->Size = System::Drawing::Size(210, 24);
			this->readToolStripMenuItem->Text = L"Read Image";
			this->readToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::readToolStripMenuItem_Click);
			// 
			// grayImageToolStripMenuItem
			// 
			this->grayImageToolStripMenuItem->Name = L"grayImageToolStripMenuItem";
			this->grayImageToolStripMenuItem->Size = System::Drawing::Size(210, 24);
			this->grayImageToolStripMenuItem->Text = L"Gray Image";
			this->grayImageToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::grayImageToolStripMenuItem_Click);
			// 
			// histogramToolStripMenuItem
			// 
			this->histogramToolStripMenuItem->Name = L"histogramToolStripMenuItem";
			this->histogramToolStripMenuItem->Size = System::Drawing::Size(210, 24);
			this->histogramToolStripMenuItem->Text = L"Histogram";
			this->histogramToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::histogramToolStripMenuItem_Click);
			// 
			// kMEANSThresholdToolStripMenuItem
			// 
			this->kMEANSThresholdToolStripMenuItem->Name = L"kMEANSThresholdToolStripMenuItem";
			this->kMEANSThresholdToolStripMenuItem->Size = System::Drawing::Size(210, 24);
			this->kMEANSThresholdToolStripMenuItem->Text = L"K-MEANS Threshold";
			this->kMEANSThresholdToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::kMEANSThresholdToolStripMenuItem_Click);
			// 
			// invertBinaryImageToolStripMenuItem
			// 
			this->invertBinaryImageToolStripMenuItem->Name = L"invertBinaryImageToolStripMenuItem";
			this->invertBinaryImageToolStripMenuItem->Size = System::Drawing::Size(210, 24);
			this->invertBinaryImageToolStripMenuItem->Text = L"Invert Binary Image";
			this->invertBinaryImageToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::invertBinaryImageToolStripMenuItem_Click);
			// 
			// morphologyToolStripMenuItem
			// 
			this->morphologyToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->erosionToolStripMenuItem,
					this->dilationToolStripMenuItem, this->openingToolStripMenuItem, this->closingToolStripMenuItem
			});
			this->morphologyToolStripMenuItem->Name = L"morphologyToolStripMenuItem";
			this->morphologyToolStripMenuItem->Size = System::Drawing::Size(99, 23);
			this->morphologyToolStripMenuItem->Text = L"Morphology";
			// 
			// erosionToolStripMenuItem
			// 
			this->erosionToolStripMenuItem->Name = L"erosionToolStripMenuItem";
			this->erosionToolStripMenuItem->Size = System::Drawing::Size(139, 24);
			this->erosionToolStripMenuItem->Text = L"Erosion";
			this->erosionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::erosionToolStripMenuItem_Click);
			// 
			// dilationToolStripMenuItem
			// 
			this->dilationToolStripMenuItem->Name = L"dilationToolStripMenuItem";
			this->dilationToolStripMenuItem->Size = System::Drawing::Size(139, 24);
			this->dilationToolStripMenuItem->Text = L"Dilation";
			this->dilationToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::dilationToolStripMenuItem_Click);
			// 
			// openingToolStripMenuItem
			// 
			this->openingToolStripMenuItem->Name = L"openingToolStripMenuItem";
			this->openingToolStripMenuItem->Size = System::Drawing::Size(139, 24);
			this->openingToolStripMenuItem->Text = L"Opening";
			this->openingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::openingToolStripMenuItem_Click);
			// 
			// closingToolStripMenuItem
			// 
			this->closingToolStripMenuItem->Name = L"closingToolStripMenuItem";
			this->closingToolStripMenuItem->Size = System::Drawing::Size(139, 24);
			this->closingToolStripMenuItem->Text = L"Closing";
			this->closingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::closingToolStripMenuItem_Click);
			// 
			// labellingToolStripMenuItem
			// 
			this->labellingToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->rGBLabellingToolStripMenuItem,
					this->objectDectectToolStripMenuItem
			});
			this->labellingToolStripMenuItem->Name = L"labellingToolStripMenuItem";
			this->labellingToolStripMenuItem->Size = System::Drawing::Size(77, 23);
			this->labellingToolStripMenuItem->Text = L"Labelling";
			// 
			// rGBLabellingToolStripMenuItem
			// 
			this->rGBLabellingToolStripMenuItem->Name = L"rGBLabellingToolStripMenuItem";
			this->rGBLabellingToolStripMenuItem->Size = System::Drawing::Size(170, 24);
			this->rGBLabellingToolStripMenuItem->Text = L"RGB Labelling";
			this->rGBLabellingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::rGBLabellingToolStripMenuItem_Click);
			// 
			// objectDectectToolStripMenuItem
			// 
			this->objectDectectToolStripMenuItem->Name = L"objectDectectToolStripMenuItem";
			this->objectDectectToolStripMenuItem->Size = System::Drawing::Size(170, 24);
			this->objectDectectToolStripMenuItem->Text = L"Object Detect";
			this->objectDectectToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::objectDectectToolStripMenuItem_Click);
			// 
			// featureProcessToolStripMenuItem
			// 
			this->featureProcessToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->featureExtractionToolStripMenuItem,
					this->saveDatabaseToolStripMenuItem
			});
			this->featureProcessToolStripMenuItem->Name = L"featureProcessToolStripMenuItem";
			this->featureProcessToolStripMenuItem->Size = System::Drawing::Size(119, 23);
			this->featureProcessToolStripMenuItem->Text = L"Feature Process";
			// 
			// featureExtractionToolStripMenuItem
			// 
			this->featureExtractionToolStripMenuItem->Name = L"featureExtractionToolStripMenuItem";
			this->featureExtractionToolStripMenuItem->Size = System::Drawing::Size(196, 24);
			this->featureExtractionToolStripMenuItem->Text = L"Feature Extraction";
			this->featureExtractionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::featureExtractionToolStripMenuItem_Click);
			// 
			// saveDatabaseToolStripMenuItem
			// 
			this->saveDatabaseToolStripMenuItem->Name = L"saveDatabaseToolStripMenuItem";
			this->saveDatabaseToolStripMenuItem->Size = System::Drawing::Size(196, 24);
			this->saveDatabaseToolStripMenuItem->Text = L"Save Database";
			this->saveDatabaseToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::saveDatabaseToolStripMenuItem_Click);
			// 
			// testImageToolStripMenuItem
			// 
			this->testImageToolStripMenuItem->Name = L"testImageToolStripMenuItem";
			this->testImageToolStripMenuItem->Size = System::Drawing::Size(89, 23);
			this->testImageToolStripMenuItem->Text = L"Test Image";
			this->testImageToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::testImageToolStripMenuItem_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(9, 32);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(700, 700);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
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
			this->listBox1->Location = System::Drawing::Point(1264, 49);
			this->listBox1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(180, 290);
			this->listBox1->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(1262, 32);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(118, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Hu Moments of Objects";
			// 
			// listBox2
			// 
			this->listBox2->FormattingEnabled = true;
			this->listBox2->Location = System::Drawing::Point(1264, 367);
			this->listBox2->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(180, 225);
			this->listBox2->TabIndex = 5;
			// 
			// histogramChart
			// 
			chartArea1->Name = L"ChartArea1";
			this->histogramChart->ChartAreas->Add(chartArea1);
			legend1->Enabled = false;
			legend1->Name = L"Legend1";
			this->histogramChart->Legends->Add(legend1);
			this->histogramChart->Location = System::Drawing::Point(776, 32);
			this->histogramChart->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->histogramChart->Name = L"histogramChart";
			this->histogramChart->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::SeaGreen;
			series1->ChartArea = L"ChartArea1";
			series1->Legend = L"Legend1";
			series1->Name = L"Histogram";
			this->histogramChart->Series->Add(series1);
			this->histogramChart->Size = System::Drawing::Size(462, 308);
			this->histogramChart->TabIndex = 6;
			this->histogramChart->Text = L"chart1";
			this->histogramChart->Visible = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(727, 380);
			this->pictureBox2->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(287, 199);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox2->TabIndex = 7;
			this->pictureBox2->TabStop = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(1262, 352);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(86, 13);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Center of Gravity";
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->textBox1->Location = System::Drawing::Point(1286, 596);
			this->textBox1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(142, 41);
			this->textBox1->TabIndex = 9;
			this->textBox1->Visible = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(1286, 642);
			this->button1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(141, 43);
			this->button1->TabIndex = 10;
			this->button1->Text = L"DB Save Moments";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Visible = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// listBox3
			// 
			this->listBox3->FormattingEnabled = true;
			this->listBox3->Location = System::Drawing::Point(1067, 367);
			this->listBox3->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->listBox3->Name = L"listBox3";
			this->listBox3->Size = System::Drawing::Size(180, 225);
			this->listBox3->TabIndex = 11;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(1065, 352);
			this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(59, 13);
			this->label3->TabIndex = 12;
			this->label3->Text = L"Predictions";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1443, 687);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->listBox3);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->histogramChart);
			this->Controls->Add(this->listBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"MyForm";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->histogramChart))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		// ----- READ IMAGE -------------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------------------------
		private: System::Void readToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			CString str;
			LPCTSTR input;
			if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				str = openFileDialog1->FileName;
				input = (LPCTSTR)str;
				// BMP image okumak
				Buffer = LoadBMP(Width, Height, Size, input);

				pictureBox1->Width = Width;
				pictureBox1->Height = Height;
				this->pictureBox1->ImageLocation = openFileDialog1->FileName;
			}
		}
		
		// ----- RGB TO GRAY IMAGE ------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------------------------
		private: System::Void grayImageToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			Raw_Intensity = ConvertToIntensity(Buffer, Width, Height);
			ShowIntensity(Raw_Intensity, Width, Height, pictureBox1);
		}

		// ----- HISTOGRAM --------------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------------------------
		private: System::Void histogramToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			Histogram_Values = Histogram(Raw_Intensity, Width, Height);
			this->histogramChart->Visible = true;
			this->histogramChart->Series["Histogram"]->Points->Clear();

			int temp = 0;
			for (int i = 0; i < 256; i++) {
				this->histogramChart->Series["Histogram"]->Points->AddXY(i, Histogram_Values[i]);
			}
		}

		// ----- K-MEANS THRESHOLD ------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------------------------
		private: System::Void kMEANSThresholdToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			Binary_Image = KMeansThreshold(Raw_Intensity, Width, Height, 2);
			ShowIntensity(Binary_Image, Width, Height, pictureBox1);
		}

		// ----- INVERT BINARY IMAGE ----------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------------------------
		private: System::Void invertBinaryImageToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			Binary_Image = InvertBinaryImage(Binary_Image, Width, Height);
			ShowIntensity(Binary_Image, Width, Height, pictureBox1);
		}

		// ----- COLOR LABELING ---------------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------------------------
		private: System::Void rGBLabellingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			int total_label = 1;
			BYTE* Labeled_Image = Labeling(Binary_Image, Width, Height, total_label); // totalLabel 1 fazla geliyor dikkat

			// Labellara renk atamasý gerçekleþitirilir.
			srand(time(0));
			int* colors = new int[total_label*3] {0};
			for (int i = 0; i < total_label * 3; i++)
				colors[i] = int(rand() % 256);

			ShowLabelingRGBImage(Labeled_Image, Width, Height, pictureBox1, colors);
		}

		// ----- OBJECT DETECT ----------------------------------------------------------------------------------------
	    //-------------------------------------------------------------------------------------------------------------
		private: System::Void objectDectectToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			int total_label = 1;
			int size = Width * Height;
			BYTE* Labeled_Image = Labeling(Binary_Image, Width, Height, total_label);
			Boxes* Objects = Segment(Labeled_Image, Width, Height, total_label - 1);

			// Object Rectangle
			for (int k = 0; k < total_label - 1; k++) {
				Boxes object = Objects[k];
				for (int i = object.top_col; i <= object.bottom_col; i++)
				{
					((Bitmap^)pictureBox1->Image)->SetPixel(i, object.top_row, Color::FromArgb(255, 0, 0));
					((Bitmap^)pictureBox1->Image)->SetPixel(i, object.bottom_row, Color::FromArgb(255, 0, 0));
					pictureBox1->Refresh();
				}
				for (int j = object.top_row; j <= object.bottom_row; j++)
				{
					((Bitmap^)pictureBox1->Image)->SetPixel(object.top_col, j, Color::FromArgb(255, 0, 0));
					((Bitmap^)pictureBox1->Image)->SetPixel(object.bottom_col, j, Color::FromArgb(255, 0, 0));
					pictureBox1->Refresh();
				}
			}
		}

		// ----- EROSION ----------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------------------------
		private: System::Void erosionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			MASK* mask = new MASK(3, 3);
			Binary_Image = Erosion(Binary_Image, Width, Height, mask);
			ShowIntensity(Binary_Image, Width, Height, pictureBox1);
		}
		
		// ----- DILATION ---------------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------------------------
		private: System::Void dilationToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			MASK* mask = new MASK(3, 3);
			Binary_Image = Dilation(Binary_Image, Width, Height, mask);
			ShowIntensity(Binary_Image, Width, Height, pictureBox1);
		}

		// ----- OPENING ----------------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------------------------
		private: System::Void openingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			MASK* mask = new MASK(3, 3);
			Binary_Image = Opening(Binary_Image, Width, Height, mask);
			ShowIntensity(Binary_Image, Width, Height, pictureBox1);
		}

		// ----- CLOSING ----------------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------------------------
		private: System::Void closingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			MASK* mask = new MASK(3, 3);
			Binary_Image = ClosingMorphology(Binary_Image, Width, Height, mask);
			ShowIntensity(Binary_Image, Width, Height, pictureBox1);		
		}

		// ----- FEATURE EXTRACTION WITH HU MOMENTS -------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------------------------
		private: System::Void featureExtractionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			int total_label = 1;
			BYTE* Labeled_Image = Labeling(Binary_Image, Width, Height, total_label);
			Boxes* Objects = Segment(Labeled_Image, Width, Height, total_label - 1);
			moments = FeatureExtract(Objects, Binary_Image, (total_label - 1), Width);

			this->listBox2->Items->Clear();
			for (int i = 0; i < 7; i++)
			{
				this->listBox2->Items->Add(moments[i]);
			}
			this->saveDatabaseToolStripMenuItem->Enabled = true;
		}

		// ----- SAVE DATABASE ----------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------------------------
		private: System::Void saveDatabaseToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			this->textBox1->Visible = true;
			this->button1->Visible = true;
		}
		private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			String^ textbox = this->textBox1->Text;
			char* text = (char*)(void*)Marshal::StringToHGlobalAnsi(textbox); // String^ to char*
			if (text != "") {
				SaveDatabase(db, db_moment_count, moments, text);

				for (int i = 0; i < 7; i++)
				{
					listBox1->Items->Add(db[db_moment_count].fiMoments[i]);
				}
				String^ clistr = gcnew String(db[db_moment_count].labelName); // char* to String^
				listBox1->Items->Add(clistr);
				db_moment_count++;
				this->textBox1->Clear();
				this->textBox1->Visible = false;
				this->button1->Visible = false;
				this->saveDatabaseToolStripMenuItem->Enabled = false;
			}
			else {
				MessageBox::Show("Please write the label of the feature data you want to save.");
			}
		}

		// ----- TEST IMAGE -------------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------------------------
		private: System::Void testImageToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
			DB_MOMENT* objects = new DB_MOMENT[4];
			objects[0].labelName = "mercimek"; //kýrmýzý
			objects[0].fiMoments[0] = 0.00062970251229307178;
			objects[0].fiMoments[1] = 5.6530171444148748E-09;
			objects[0].fiMoments[2] = 2.2206410033167037E-12;
			objects[0].fiMoments[3] = 1.4349544860238779E-14;
			objects[0].fiMoments[4] = 4.9003554831775543E-27;
			objects[0].fiMoments[5] = 1.0333965188677294E-18;
			objects[0].fiMoments[6] = 2.1246471352897949E-27;

			objects[1].labelName = "badem"; // yeþil
			objects[1].fiMoments[0] = 0.00070825679849337655;
			objects[1].fiMoments[1] = 1.0729847808018249E-07;
			objects[1].fiMoments[2] = 7.2439331965337138E-12;
			objects[1].fiMoments[3] = 5.7095393946652563E-13;
			objects[1].fiMoments[4] = 1.4196082712249309E-24;
			objects[1].fiMoments[5] = 1.5281762501959781E-16;
			objects[1].fiMoments[6] = 8.8529973900890457E-25;

			objects[2].labelName = "cubuk"; // mavi
			objects[2].fiMoments[0] = 0.0048551509537239964;
			objects[2].fiMoments[1] = 1.5126307764162974E-05;
			objects[2].fiMoments[2] = 1.1385172171885264E-08;
			objects[2].fiMoments[3] = 1.8639089411876898E-09;
			objects[2].fiMoments[4] = 1.5273921565415879E-17;
			objects[2].fiMoments[5] = 2.5717959126843983E-12;
			objects[2].fiMoments[6] = 7.78660672712528E-18;

			objects[3].labelName = "nohut"; // sarý
			objects[3].fiMoments[0] = 0.00064960300076415372;
			objects[3].fiMoments[1] = 2.6206039478254018E-08;
			objects[3].fiMoments[2] = 3.5423232180505742E-12;
			objects[3].fiMoments[3] = 6.6000836682146728E-14;
			objects[3].fiMoments[4] = 2.0397253014587417E-26;
			objects[3].fiMoments[5] = 4.664320993650335E-18;
			objects[3].fiMoments[6] = 6.57183127623146E-26;


			listBox3->Items->Clear();

			int total_label = 1;
			BYTE* Labeled_Image = Labeling(Binary_Image, Width, Height, total_label);
			Boxes* Objects = Segment(Labeled_Image, Width, Height, total_label - 1);
			PREDICTION* predictions = Testing(Objects, Binary_Image, db, db_moment_count, (total_label - 1), Width);

			srand(time(0));
			int* colors = new int[db_moment_count * 3]{ 0 };
			for (int i = 0; i < db_moment_count * 3; i++)
				colors[i] = int(rand() % 256);
			
			int* counts = new int[db_moment_count] {0};

			for (int i = 0; i < total_label-1; i++) {
				Boxes object = Objects[i];

				String^ clistr = gcnew String(predictions[i].name); // char* to String^
				listBox3->Items->Add(i);
				listBox3->Items->Add(clistr);
				listBox3->Items->Add(predictions[i].distance);
				int idValue = predictions[i].id;
				counts[idValue]++;
				// Tahminleri sýnýflara göre renklendirme iþlemi
				for (int k = object.top_row; k <= object.bottom_row; k++)
				{
					for (int j = object.top_col; j <= object.bottom_col; j++)
					{
						int point = Labeled_Image[k * Width + j];
						int value = idValue * 3;
						if (point == object.label) {
							((Bitmap^)pictureBox1->Image)->SetPixel(j, k, Color::FromArgb(colors[value], colors[value + 1], colors[value + 2]));
						}						
					}
				}
			}
			pictureBox1->Refresh();

			// Nesnelerin adedini bastýrma
			for (int i = 0; i < db_moment_count; i++) {
				String^ clistr = gcnew String(db[i].labelName); // char* to String^
				listBox3->Items->Add(clistr);
				listBox3->Items->Add(counts[i]);
			}
		}
	};
}

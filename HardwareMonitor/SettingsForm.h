#pragma once

namespace HardwareMonitor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// SettingsForm ժҪ
	/// </summary>
	public ref class SettingsForm : public System::Windows::Forms::Form
	{
	public:
        SettingsForm(void);

	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
		/// </summary>
		~SettingsForm()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::Windows::Forms::ListBox^ monitorItemListBox;
    private: System::Windows::Forms::Button^ removeSelectBtn;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Button^ cancelBtn;
    private: System::Windows::Forms::Button^ okBtn;
    protected:

	private:
		/// <summary>
		/// ����������������
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����֧������ķ��� - ��Ҫ�޸�
		/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
		/// </summary>
		void InitializeComponent(void)
		{
            this->monitorItemListBox = (gcnew System::Windows::Forms::ListBox());
            this->removeSelectBtn = (gcnew System::Windows::Forms::Button());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->cancelBtn = (gcnew System::Windows::Forms::Button());
            this->okBtn = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // monitorItemListBox
            // 
            this->monitorItemListBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
                | System::Windows::Forms::AnchorStyles::Left)
                | System::Windows::Forms::AnchorStyles::Right));
            this->monitorItemListBox->FormattingEnabled = true;
            this->monitorItemListBox->ItemHeight = 20;
            this->monitorItemListBox->Location = System::Drawing::Point(14, 36);
            this->monitorItemListBox->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->monitorItemListBox->Name = L"monitorItemListBox";
            this->monitorItemListBox->Size = System::Drawing::Size(294, 224);
            this->monitorItemListBox->TabIndex = 0;
            // 
            // removeSelectBtn
            // 
            this->removeSelectBtn->Location = System::Drawing::Point(321, 36);
            this->removeSelectBtn->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->removeSelectBtn->Name = L"removeSelectBtn";
            this->removeSelectBtn->Size = System::Drawing::Size(112, 31);
            this->removeSelectBtn->TabIndex = 1;
            this->removeSelectBtn->Text = L"�Ƴ�ѡ����";
            this->removeSelectBtn->UseVisualStyleBackColor = true;
            this->removeSelectBtn->Click += gcnew System::EventHandler(this, &SettingsForm::removeSelectBtn_Click);
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(12, 9);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(114, 20);
            this->label1->TabIndex = 2;
            this->label1->Text = L"����Ӽ���";
            // 
            // cancelBtn
            // 
            this->cancelBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
            this->cancelBtn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->cancelBtn->Location = System::Drawing::Point(358, 286);
            this->cancelBtn->Name = L"cancelBtn";
            this->cancelBtn->Size = System::Drawing::Size(75, 29);
            this->cancelBtn->TabIndex = 3;
            this->cancelBtn->Text = L"ȡ��";
            this->cancelBtn->UseVisualStyleBackColor = true;
            // 
            // okBtn
            // 
            this->okBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
            this->okBtn->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->okBtn->Location = System::Drawing::Point(277, 286);
            this->okBtn->Name = L"okBtn";
            this->okBtn->Size = System::Drawing::Size(75, 29);
            this->okBtn->TabIndex = 3;
            this->okBtn->Text = L"ȷ��";
            this->okBtn->UseVisualStyleBackColor = true;
            // 
            // SettingsForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(445, 327);
            this->Controls->Add(this->okBtn);
            this->Controls->Add(this->cancelBtn);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->removeSelectBtn);
            this->Controls->Add(this->monitorItemListBox);
            this->Font = (gcnew System::Drawing::Font(L"΢���ź�", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(134)));
            this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->Name = L"SettingsForm";
            this->Text = L"SettingsForm";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
    private:
        System::Void removeSelectBtn_Click(System::Object^ sender, System::EventArgs^ e);
    };
}

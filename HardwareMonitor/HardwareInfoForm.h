#pragma once

namespace HardwareMonitor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// HardwareInfoForm ժҪ
	/// </summary>
	public ref class HardwareInfoForm : public System::Windows::Forms::Form
	{
	public:
        HardwareInfoForm(void);

        void UpdateData();

	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
		/// </summary>
		~HardwareInfoForm()
		{
			if (components)
			{
				delete components;
			}
		}

        void InitUserComponent();

    private:
        void AddItem_Click(System::Object^ sender, System::EventArgs^ e);
        void ContextMenuStrip_Opening(Object^ sender, CancelEventArgs^ e);
        void TreeView_MouseClick(Object^ sender, MouseEventArgs^ e);
        void TreeView_DrawNode(Object^ sender, DrawTreeNodeEventArgs^ e);

    private: System::Windows::Forms::TreeView^ treeView1;

    private: System::ComponentModel::IContainer^ components;
    protected:
        System::Windows::Forms::ContextMenuStrip^ contextMenuStrip;
    private: System::Windows::Forms::CheckBox^ autoRefreshCheck;
    protected:

    protected:
        ToolStripMenuItem^ addItem;

	private:
		/// <summary>
		/// ����������������
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����֧������ķ��� - ��Ҫ�޸�
		/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
		/// </summary>
		void InitializeComponent(void)
		{
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(HardwareInfoForm::typeid));
            this->treeView1 = (gcnew System::Windows::Forms::TreeView());
            this->autoRefreshCheck = (gcnew System::Windows::Forms::CheckBox());
            this->SuspendLayout();
            resources->ApplyResources(this->treeView1, L"treeView1");
            this->treeView1->Name = L"treeView1";
            resources->ApplyResources(this->autoRefreshCheck, L"autoRefreshCheck");
            this->autoRefreshCheck->Name = L"autoRefreshCheck";
            this->autoRefreshCheck->UseVisualStyleBackColor = true;
            this->autoRefreshCheck->CheckedChanged += gcnew System::EventHandler(this, &HardwareInfoForm::autoRefreshCheck_CheckedChanged);
            resources->ApplyResources(this, L"$this");
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->Controls->Add(this->autoRefreshCheck);
            this->Controls->Add(this->treeView1);
            this->Name = L"HardwareInfoForm";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
    private: System::Void autoRefreshCheck_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
    };
}

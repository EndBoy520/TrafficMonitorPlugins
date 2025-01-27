#include "stdafx.h"
#include "SettingsForm.h"
#include "HardwareMonitor.h"
#include "HardwareMonitorHelper.h"

namespace HardwareMonitor
{
    SettingsForm::SettingsForm(void)
    {
        this->StartPosition = FormStartPosition::CenterParent;
        InitializeComponent();
        UpdateItemList();

        //���Ƴ�����ť��ʼΪ����״̬
        removeSelectBtn->Enabled = false;

        // ΪListBox��SelectedIndexChanged�¼���Ӵ������
        monitorItemListBox->SelectedIndexChanged += gcnew System::EventHandler(this, &SettingsForm::listBox_SelectedIndexChanged);
    }

    void SettingsForm::UpdateItemList()
    {
        //����б�
        monitorItemListBox->Items->Clear();

        //�������
        for (const auto& identifyer : CHardwareMonitor::GetInstance()->m_settings.item_identifyers)
        {
            String^ item_name = gcnew String(CHardwareMonitor::GetInstance()->GetItemName(identifyer).c_str());
            if (item_name->Length > 0)
                monitorItemListBox->Items->Add(item_name);
        }
    }

    void SettingsForm::listBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
    {
        // �����Ƿ���ѡ�������û���ð�ť
        removeSelectBtn->Enabled = monitorItemListBox->SelectedIndex >= 0;
    }

    System::Void SettingsForm::removeSelectBtn_Click(System::Object^ sender, System::EventArgs^ e)
    {
        int selectedIndex = monitorItemListBox->SelectedIndex;
        // ɾ��ListBox�е�ѡ����
        if (selectedIndex >= 0)
        {
            // ����MessageBoxѯ���û��Ƿ�Ҫɾ��
            System::Windows::Forms::DialogResult result = System::Windows::Forms::MessageBox::Show(
                MonitorGlobal::Instance()->GetString(L"RemoveMonitorItemInquery"),
                MonitorGlobal::Instance()->GetString(L"PluginName"),
                System::Windows::Forms::MessageBoxButtons::OKCancel, 
                System::Windows::Forms::MessageBoxIcon::Question);
            // ����û������ȷ��������ɾ��ѡ����
            if (result == System::Windows::Forms::DialogResult::OK)
            {
                monitorItemListBox->Items->RemoveAt(selectedIndex);
                CHardwareMonitor::GetInstance()->RemoveDisplayItem(selectedIndex);
            }
        }
    }

    System::Void SettingsForm::addItemBtn_Click(System::Object^ sender, System::EventArgs^ e)
    {
        MonitorGlobal::Instance()->ShowHardwareInfoDialog();
        UpdateItemList();
    }

}

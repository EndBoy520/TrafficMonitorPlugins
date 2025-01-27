#include "stdafx.h"
#include "SettingsForm.h"
#include "HardwareMonitor.h"
#include "HardwareMonitorHelper.h"

namespace HardwareMonitor
{
    SettingsForm::SettingsForm(void)
    {
        this->StartPosition = FormStartPosition::CenterParent;
        this->Icon = MonitorGlobal::Instance()->GetAppIcon();
        InitializeComponent();
        UpdateItemList();

        //���Ƴ�����ť��ʼΪ����״̬
        removeSelectBtn->Enabled = false;

        //��ʼ��Ҫ��ص�Ӳ��ѡ��
        Computer^ computer = MonitorGlobal::Instance()->computer;
        cpuCheck->Checked = computer->IsCpuEnabled;
        gpuCheck->Checked = computer->IsGpuEnabled;
        motherBoardCheck->Checked = computer->IsMotherboardEnabled;
        storageCheck->Checked = computer->IsStorageEnabled;
        batteryCheck->Checked = computer->IsBatteryEnabled;
        networkCheck->Checked = computer->IsNetworkEnabled;

        // ΪListBox��SelectedIndexChanged�¼���Ӵ������
        monitorItemListBox->SelectedIndexChanged += gcnew System::EventHandler(this, &SettingsForm::listBox_SelectedIndexChanged);

        // ΪFormClosing�¼���Ӵ������
        this->FormClosing += gcnew FormClosingEventHandler(this, &SettingsForm::OnFormClosing);
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

    void SettingsForm::OnFormClosing(Object^ sender, FormClosingEventArgs^ e)
    {
        //����Ҫ��ص�Ӳ������
        Computer^ computer = MonitorGlobal::Instance()->computer;
        computer->IsCpuEnabled = cpuCheck->Checked;
        computer->IsGpuEnabled = gpuCheck->Checked;
        computer->IsMotherboardEnabled = storageCheck->Checked;
        computer->IsStorageEnabled = storageCheck->Checked;
        computer->IsBatteryEnabled = batteryCheck->Checked;
        computer->IsNetworkEnabled = networkCheck->Checked;

        //��������
        CHardwareMonitor::GetInstance()->SaveConfig();
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

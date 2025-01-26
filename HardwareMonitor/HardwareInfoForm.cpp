#include "stdafx.h"
#include "HardwareInfoForm.h"
#include "HardwareMonitor.h"
#include <cliext/map>
#include "HardwareMonitorHelper.h"

namespace HardwareMonitor
{

    HardwareInfoForm::HardwareInfoForm(void)
    {
        InitializeComponent();
        InitContextMenu();

        //�������
        auto computer = MonitorGlobal::Instance()->computer;
        for (int i = 0; i < computer->Hardware->Count; i++)
        {
            //���Hardware�ڵ�
            auto hardware = computer->Hardware[i];
            auto hardware_node = treeView1->Nodes->Add(hardware->Name);
            //���Sensor�ڵ�
            typedef cliext::map<SensorType, TreeNode^> TypeNodeMap;
            TypeNodeMap sensor_type_nodes;       //��������Sensor���͵Ľڵ�
            for (int j = 0; j < hardware->Sensors->Length; j++)
            {
                auto sensor = hardware->Sensors[j];
                //����Sensor�����ʹ������ڵ�
                TreeNode^ type_node;
                TypeNodeMap::iterator iter = sensor_type_nodes.find(sensor->SensorType);
                if (iter == sensor_type_nodes.end())
                {
                    //�������ͽڵ㣬�����浽map��
                    type_node = hardware_node->Nodes->Add(gcnew String(HardwareMonitorHelper::GetSensorTypeName(sensor->SensorType)));
                    sensor_type_nodes.insert(TypeNodeMap::make_value(sensor->SensorType, type_node));
                }
                else
                {
                    //�Ѵ��ڵĽڵ�
                    type_node = iter->second;
                }

                String^ sensor_str = HardwareMonitorHelper::GetSensorNameValueText(sensor);
                auto sensor_node = type_node->Nodes->Add(sensor_str);
                sensor_node->Tag = sensor->Identifier->ToString();
            }
        }

        //չ�����нڵ�
        treeView1->ExpandAll();
    }

    void HardwareMonitor::HardwareInfoForm::UpdateData()
    {
        treeView1->BeginUpdate();
        //�������ڵ������
        //����Hardware�ڵ�
        for each (TreeNode ^ hardware_node in treeView1->Nodes)
        {
            //����SensorType�ڵ�
            for each (TreeNode ^ sensor_type_node in hardware_node->Nodes)
            {
                //����Sensor�ڵ�
                for each (TreeNode ^ sensor_node in sensor_type_node->Nodes)
                {
                    String^ identifyer = sensor_node->Tag->ToString();
                    ISensor^ sensor = HardwareMonitorHelper::FindSensorByIdentifyer(identifyer);
                    if (sensor != nullptr)
                    {
                        String^ sensor_str = HardwareMonitorHelper::GetSensorNameValueText(sensor);
                        sensor_node->Text = sensor_str;
                    }
                }
            }
        }
        treeView1->EndUpdate();
    }

    void HardwareInfoForm::InitContextMenu()
    {
        contextMenuStrip = gcnew System::Windows::Forms::ContextMenuStrip();

        // ��Ӳ˵���
        addItem = gcnew ToolStripMenuItem();
        addItem->Text = MonitorGlobal::Instance()->GetString(L"AddToMonitorItem");
        addItem->Click += gcnew EventHandler(this, &HardwareInfoForm::AddItem_Click);
        contextMenuStrip->Opening += gcnew CancelEventHandler(this, &HardwareInfoForm::ContextMenuStrip_Opening);

        // ���˵�����ӵ� ContextMenuStrip
        contextMenuStrip->Items->Add(addItem);

        // �� ContextMenuStrip �󶨵� TreeView
        treeView1->ContextMenuStrip = contextMenuStrip;

        // ��� MouseClick �¼��������
        treeView1->MouseClick += gcnew MouseEventHandler(this, &HardwareInfoForm::TreeView_MouseClick);
    }

    void HardwareInfoForm::AddItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // ��ȡѡ�еĽڵ�
        TreeNode^ selectedNode = treeView1->SelectedNode;
        if (selectedNode != nullptr && selectedNode->Tag != nullptr)
        {
            String^ identifyer = selectedNode->Tag->ToString();
            ISensor^ sensor = HardwareMonitorHelper::FindSensorByIdentifyer(identifyer);
            if (CHardwareMonitor::GetInstance()->AddDisplayItem(sensor))
                CHardwareMonitor::GetInstance()->SaveConfig();
            else
                MessageBox::Show(MonitorGlobal::Instance()->GetString(L"AddItemFailedMsg"));
        }
    }

    void HardwareInfoForm::ContextMenuStrip_Opening(Object^ sender, CancelEventArgs^ e)
    {
        TreeNode^ selectedNode = treeView1->SelectedNode;
        // ����Ƿ�Ϊ�� 3 ���ڵ㣨����3���ڵ�������Ӽ����Ŀ��
        if (selectedNode != nullptr && selectedNode->Parent != nullptr && selectedNode->Parent->Parent != nullptr)
            addItem->Enabled = true;
        else
            addItem->Enabled = false;
    }

    void HardwareInfoForm::TreeView_MouseClick(Object^ sender, MouseEventArgs^ e)
    {
        if (e->Button == System::Windows::Forms::MouseButtons::Right)
        {
            // ��ȡ���λ�õĽڵ�
            TreeNode^ clickedNode = treeView1->GetNodeAt(e->X, e->Y);
            if (clickedNode != nullptr)
            {
                // ѡ�е���Ľڵ�
                treeView1->SelectedNode = clickedNode;
            }
        }
    }
}

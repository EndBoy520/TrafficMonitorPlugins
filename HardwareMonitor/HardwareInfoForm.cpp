#include "stdafx.h"
#include "HardwareInfoForm.h"
#include "HardwareMonitor.h"
#include <cliext/map>
#include "HardwareMonitorHelper.h"

namespace HardwareMonitor
{
    static TreeNode^ AddHardwareNode(TreeNodeCollection^ nodes, IHardware^ hardware)
    {
        auto hardware_node = nodes->Add(hardware->Name);
        switch (hardware->HardwareType)
        {
        case HardwareType::Motherboard: hardware_node->ImageIndex = 0; break;
        case HardwareType::Battery: hardware_node->ImageIndex = 1; break;
        case HardwareType::Cpu: hardware_node->ImageIndex = 2; break;
        case HardwareType::EmbeddedController: hardware_node->ImageIndex = 3; break;
        case HardwareType::Network: hardware_node->ImageIndex = 4; break;
        case HardwareType::Memory: hardware_node->ImageIndex = 5; break;
        case HardwareType::Storage: hardware_node->ImageIndex = 6; break;
        case HardwareType::GpuAmd: hardware_node->ImageIndex = 7; break;
        case HardwareType::GpuIntel: hardware_node->ImageIndex = 8; break;
        case HardwareType::GpuNvidia: hardware_node->ImageIndex = 9; break;
        }
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
            sensor_node->Tag = HardwareMonitorHelper::GetSensorIdentifyer(sensor);
        }
        return hardware_node;
    }

    HardwareInfoForm::HardwareInfoForm(void)
    {
        this->StartPosition = FormStartPosition::CenterParent;
        this->Icon = MonitorGlobal::Instance()->GetAppIcon();

        InitializeComponent();
        InitUserComponent();

        //�������
        auto computer = MonitorGlobal::Instance()->computer;
        for (int i = 0; i < computer->Hardware->Count; i++)
        {
            //���Hardware�ڵ�
            auto hardware = computer->Hardware[i];
            auto hardware_node = AddHardwareNode(treeView1->Nodes, hardware);
            //����SubHardware
            for (int j = 0; j < hardware->SubHardware->Length; j++)
            {
                auto sub_hardware = hardware->SubHardware[j];
                AddHardwareNode(hardware_node->Nodes, sub_hardware);
            }
        }

        //չ�����нڵ�
        treeView1->ExpandAll();
    }

    //����һ�����ڵ��ֵ
    static void UpdateNodeValue(TreeNode^ node)
    {
        //���ӽڵ���ݹ����
        if (node->Nodes->Count != 0)
        {
            for each (TreeNode ^ sub_node in node->Nodes)
            {
                UpdateNodeValue(sub_node);
            }
        }
        //Ҷ�ӽڵ㣬����ֵ
        else
        {
            if (node->Tag != nullptr)
            {
                String^ identifyer = node->Tag->ToString();
                ISensor^ sensor = HardwareMonitorHelper::FindSensorByIdentifyer(identifyer);
                if (sensor != nullptr)
                {
                    String^ sensor_str = HardwareMonitorHelper::GetSensorNameValueText(sensor);
                    if (sensor_str != node->Text)
                        node->Text = sensor_str;
                }
            }
        }
    }

    void HardwareMonitor::HardwareInfoForm::UpdateData()
    {
        treeView1->BeginUpdate();
        //�������ڵ������
        //����Hardware�ڵ�
        for each (TreeNode ^ hardware_node in treeView1->Nodes)
        {
            UpdateNodeValue(hardware_node);
        }
        treeView1->EndUpdate();
    }

    void HardwareInfoForm::InitUserComponent()
    {
        // ��ʼ�� ImageList
        imageList1 = gcnew ImageList();
        int icon_size = CHardwareMonitor::GetInstance()->DPI(16);
        imageList1->ImageSize = System::Drawing::Size(icon_size, icon_size); // ����ͼ���С

        // ���ͼ�굽 ImageList
        Resources::ResourceManager^ resourceManager = MonitorGlobal::Instance()->GetResourceManager();
        imageList1->Images->Add(static_cast<Image^>(resourceManager->GetObject("MotherBoard")));
        imageList1->Images->Add(static_cast<Image^>(resourceManager->GetObject("batteries")));
        imageList1->Images->Add(static_cast<Image^>(resourceManager->GetObject("CPU")));
        imageList1->Images->Add(static_cast<Image^>(resourceManager->GetObject("FanColtroller")));
        imageList1->Images->Add(static_cast<Image^>(resourceManager->GetObject("Network")));
        imageList1->Images->Add(static_cast<Image^>(resourceManager->GetObject("RAM")));
        imageList1->Images->Add(static_cast<Image^>(resourceManager->GetObject("Storage")));
        imageList1->Images->Add(static_cast<Image^>(resourceManager->GetObject("AMD")));
        imageList1->Images->Add(static_cast<Image^>(resourceManager->GetObject("intel")));
        imageList1->Images->Add(static_cast<Image^>(resourceManager->GetObject("Nvidia")));

        // ��ʼ�� ContextMenuStrip
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

        treeView1->DrawMode = TreeViewDrawMode::OwnerDrawText; // ����Ϊ�Զ������ģʽ
        // ��� DrawNode �¼��������
        treeView1->DrawNode += gcnew DrawTreeNodeEventHandler(this, &HardwareInfoForm::TreeView_DrawNode);

        autoRefreshCheck->Checked = CHardwareMonitor::GetInstance()->m_settings.hardware_info_auto_refresh;
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
        // ����Ƿ�ΪҶ�ӽڵ㣨����Ҷ��������Ӽ����Ŀ��
        addItem->Enabled = (selectedNode != nullptr && selectedNode->Nodes->Count == 0);
    }

    void HardwareInfoForm::TreeView_MouseClick(Object^ sender, MouseEventArgs^ e)
    {
        // ��ȡ���λ�õĽڵ�
        TreeNode^ clickedNode = treeView1->GetNodeAt(e->X, e->Y);
        if (clickedNode != nullptr)
        {
            // ѡ�е���Ľڵ�
            treeView1->SelectedNode = clickedNode;
        }
    }
    void HardwareInfoForm::TreeView_DrawNode(Object^ sender, DrawTreeNodeEventArgs^ e)
    {
        // ��ȡ�ڵ�ľ�������
        Rectangle bounds = e->Bounds;
        // ��չ bounds �Ŀ�ȵ������ؼ��Ŀ��
        bounds.Width = treeView1->ClientSize.Width - bounds.Left - 1; // ��ȥ1�Ա�����Ƴ����ؼ��߽�
        System::Drawing::Color textColor;
        // ����ڵ㱻ѡ�У�����ѡ�б���
        if (e->Node == treeView1->SelectedNode)
        {
            // ����ѡ�б���
            e->Graphics->FillRectangle(gcnew SolidBrush(SystemColors::Highlight), bounds);
            textColor = SystemColors::HighlightText;
        }
        else
        {
            e->Graphics->FillRectangle(gcnew SolidBrush(SystemColors::Window), bounds);
            //�жϵ�ǰ���Ƿ�����ӵ����
            String^ identifyer{};
            if (e->Node->Tag != nullptr)
                identifyer = e->Node->Tag->ToString();
            //����ӵ������Ŀ���ı���ɫ��ʾΪ������ɫ
            if (identifyer != nullptr && CHardwareMonitor::GetInstance()->IsDisplayItemExist(MonitorGlobal::ClrStringToStdWstring(identifyer)))
                textColor = SystemColors::Highlight;
            else
                textColor = treeView1->ForeColor;
        }

        // Ϊ���ڵ����ͼ��
        if (e->Node->ImageIndex != -1 && e->Node->Parent == nullptr)
        {
            Point start_pos = bounds.Location;
            int offset = (bounds.Height - imageList1->ImageSize.Width) / 2;
            start_pos.Offset(offset, offset);
            imageList1->Draw(e->Graphics, start_pos, e->Node->ImageIndex);
            bounds.Offset(bounds.Height, 0);
            bounds.Width -= bounds.Height;
        }

        // ��ȡ�ڵ���ı�
        String^ text = e->Node->Text;

        // ����ı�
        array<String^>^ parts = System::Text::RegularExpressions::Regex::Split(text, "\\s{4}");
        if (parts->Length < 2)
            parts = gcnew array<String^>{text, ""};

        // ����������������
        SizeF rightTextSize = e->Graphics->MeasureString(parts[1], treeView1->Font);
        int rightWidth = std::min(bounds.Width, (int)rightTextSize.Width + 4);
        Rectangle rightRect = Rectangle(bounds.Right - rightWidth, bounds.Top, rightWidth, bounds.Height);
        Rectangle leftRect = Rectangle(bounds.Left, bounds.Top, bounds.Width - rightWidth, bounds.Height);

        // ���Ƶڶ������ı����Ҷ��룩
        String^ rightText = parts[1];
        TextRenderer::DrawText(e->Graphics, rightText, treeView1->Font, rightRect, textColor, TextFormatFlags::Right);

        // ���Ƶ�һ�����ı�������룩
        String^ leftText = parts[0];
        TextRenderer::DrawText(e->Graphics, leftText, treeView1->Font, leftRect, textColor, TextFormatFlags::Left | TextFormatFlags::WordEllipsis);
    }

    System::Void HardwareInfoForm::autoRefreshCheck_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
    {
        CHardwareMonitor::GetInstance()->m_settings.hardware_info_auto_refresh = autoRefreshCheck->Checked;
    }
}

#pragma once
namespace HardwareMonitor
{
    class HardwareMonitorHelper
    {
    public:
        //��ȡ��������������
        static System::String^ GetSensorTypeName(LibreHardwareMonitor::Hardware::SensorType type);

        //���ݴ��������ͻ�ȡ���ݵĵ�λ
        static const wchar_t* GetSensorTypeUnit(LibreHardwareMonitor::Hardware::SensorType type);

        //����һ����������Ψһ��ʶ������һ��������
        static LibreHardwareMonitor::Hardware::ISensor^ FindSensorByIdentifyer(System::String^ identifyer);

        //��ȡһ����������ֵ���ı�����ָ��С��λ��
        static System::String^ GetSensorValueText(LibreHardwareMonitor::Hardware::ISensor^ sensor, int decimal_place = 2);

        //��ȡһ�������������ƺ���ֵ�ı���ʹ��4���ո�ָ���
        static System::String^ GetSensorNameValueText(LibreHardwareMonitor::Hardware::ISensor^ sensor);

        //��ȡһ������������ʾ���ƣ���Ӳ�������������͡���������ɣ�ʹ�á�|���ָ�
        static System::String^ GetSensorDisplayName(LibreHardwareMonitor::Hardware::ISensor^ sensor);

        //��ȡһ����������Ψһ��ʶ��
        static System::String^ GetSensorIdentifyer(LibreHardwareMonitor::Hardware::ISensor^ sensor);
    };
}

